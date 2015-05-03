-- graphics
graphics = {}

natives.GRAPHICS.GET_SCREEN_RESOLUTION:AddCallLayout("mm)v")

-- Screen Resolution
function graphics.GetScreenResolution()
	local cX = CMemoryBlock(4)
	local cY = CMemoryBlock(4)
	
	natives.GRAPHICS.GET_SCREEN_RESOLUTION(cX, cY)
	
	local x = cX:ReadDWORD32(0)
	cX:Release()
	
	local y = cY:ReadDWORD32(0)
	cY:Release()
	
	return x, y
end