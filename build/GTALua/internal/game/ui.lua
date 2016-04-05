-- ui
ui = {}

-- Variables for tracking text position of DrawTextBlock
ui.TextBlockInfo = {
	TextX = 0,				-- X coordinate for tracking DrawTextBlock
	TextY = 0,				-- Y coordinate for tracking DrawTextBlock
	TextFont = 0,
	TextScale = .3,
	TextColor = COLOR_WHITE,
	TextBlink = false
}

-- Create Blip
function ui.CreateBlip(x,y,z)
	if type(x) == "Vector" then
		y = x.y
		z = x.z
		x = x.x
	end
	
	-- Create
	return Blip(natives.UI.ADD_BLIP_FOR_COORD(x,y,z))
end

-- Get Active Blips
function ui.GetActiveBlipsCount()
	return natives.UI.GET_NUMBER_OF_ACTIVE_BLIPS()
end

-- Draws a text onscreen with the option to have it blink
function ui.DrawTextUI(text, x, y, font, scale, color, blink)
	font = font or FontChaletComprimeCologne
	scale = scale or .5
	color = color or {r=255, g=255, b=255, a=255}
	blink = blink or false

	local draw = not blink

	if math.floor(game.GetSeconds()/10)%2 == 0 or draw then
		natives.UI.SET_TEXT_FONT(font);
		natives.UI.SET_TEXT_SCALE(0.0, scale);
		natives.UI.SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		natives.UI.SET_TEXT_CENTRE(false);
		natives.UI.SET_TEXT_OUTLINE();
		natives.UI._SET_TEXT_ENTRY("STRING");
		natives.UI.ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(string.format("%s",text));
		natives.UI._DRAW_TEXT(x, y);
	end
end

-- Read a line from the onscreen keyboard
function ui.OnscreenKeyboard(title, size)
	size = size or 20
	title = title or nil
	natives.GAMEPLAY.DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", size)
	while (natives.GAMEPLAY.UPDATE_ONSCREEN_KEYBOARD() == 0) do 
		coroutine.yield()
		if title ~= nil then
			ui.DrawTextUI(title, .3, .36)
		end
	end
	return natives.GAMEPLAY.GET_ONSCREEN_KEYBOARD_RESULT()
end

-- Draws a 3D point
function ui.Draw3DPoint(p, size, color, blink)
	size = size or 1
	blink = blink or false
	local cx = color or COLOR_RED
	local cy = color or COLOR_GREEN
	local cz = color or COLOR_BLUE
	local offset = size/2
	local px1 = p.x-offset
	local px2 = p.x+offset
	local py1 = p.y-offset
	local py2 = p.y+offset
	local pz1 = p.z-offset
	local pz2 = p.z+offset
	-- X line
	ui.Draw3DLine({x=px1, y=p.y, z=p.z}, {x=px2, y=p.y, z=p.z}, cx, blink)
	-- Y line
	ui.Draw3DLine({x=p.x, y=py1, z=p.z}, {x=p.x, y=py2, z=p.z}, cy, blink)
	-- Z line
	ui.Draw3DLine({x=p.x, y=p.y, z=pz1}, {x=p.x, y=p.y, z=pz2}, cz, blink)
end

-- Draws a 3D line
function ui.Draw3DLine(p1, p2, color, blink)
	color = color or COLOR_WHITE
	blink = blink or false
	local draw = not blink
	if math.floor(game.GetSeconds()/10)%2 == 0 or draw then
		natives.GRAPHICS.DRAW_LINE(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, color.r, color.g, color.b, color.a)
	end
end

-- Draws a 3D polygon
function ui.Draw3DPoly(p1, p2, p3, color, blink)
	color = color or COLOR_WHITE
	blink = blink or false
	local draw = not blink
	if math.floor(game.GetSeconds()/10)%2 == 0 or draw then
		natives.GRAPHICS.DRAW_POLY(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z, color.r, color.g, color.b, color.a)
	end
end

-- Draws a 3D box (solid)
function ui.Draw3DBox(p1, p2, color, blink)
	color = color or COLOR_WHITE
	blink = blink or false
	local draw = not blink
	if math.floor(game.GetSeconds()/10)%2 == 0 or draw then
		natives.GRAPHICS.DRAW_BOX(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, color.r, color.g, color.b, color.a)
	end
end

-- Draws a text block
function ui.DrawTextBlock(text, x, y, font, scale, color, blink, increment)
	ui.TextBlockInfo.TextX = x or ui.TextBlockInfo.TextX
	ui.TextBlockInfo.TextY = y or ui.TextBlockInfo.TextY
	ui.TextBlockInfo.TextFont = font or ui.TextBlockInfo.TextFont
	ui.TextBlockInfo.TextScale = scale or ui.TextBlockInfo.TextScale
	ui.TextBlockInfo.TextColor = color or ui.TextBlockInfo.TextColor
	if blink~=nil then
		ui.TextBlockInfo.TextBlink = blink
	end
	ui.DrawTextUI(text, ui.TextBlockInfo.TextX, ui.TextBlockInfo.TextY, ui.TextBlockInfo.TextFont, ui.TextBlockInfo.TextScale, ui.TextBlockInfo.TextColor, ui.TextBlockInfo.TextBlink)
	if not increment then
		ui.TextBlockInfo.TextY = ui.TextBlockInfo.TextY + (ui.TextBlockInfo.TextScale/20)
	else
		ui.TextBlockInfo.TextY = ui.TextBlockInfo.TextY + increment
	end
end

-- Shows a HUD component this frame
function ui.ShowHudComponent(component)
	natives.UI.SHOW_HUD_COMPONENT_THIS_FRAME(component)
end
