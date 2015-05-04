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