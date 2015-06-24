-- graphics
graphics = {}

-- Screen Resolution
function graphics.GetScreenResolution()
	-- alloc
	local cX = CMemoryBlock(4)
	local cY = CMemoryBlock(4)

	-- call
	natives.GRAPHICS.GET_SCREEN_RESOLUTION(cX, cY)

	-- read
	local x = cX:ReadDWORD32(0)
	local y = cY:ReadDWORD32(0)
	
	-- release
	cX:Release()
	cY:Release()

	return x, y
end

-- Screen Effect
function graphics.StartScreenEffect(name, play_lenght, loop)
	natives.GRAPHICS._START_SCREEN_EFFECT(name, play_lenght or 0, loop or false)
end

function graphics.StopScreenEffect(name)
	natives.GRAPHICS._STOP_SCREEN_EFFECT(name)
end

function graphics.ScreenEffectIsActive(name)
	return natives.GRAPHICS._GET_SCREEN_EFFECT_IS_ACTIVE(name)
end

function graphics.ClearAllScreenEffect()
	return natives.GRAPHICS._STOP_ALL_SCREEN_EFFECTS()
end
