-- ui
ui = {}

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
	font = font or 4
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
		natives.UI._ADD_TEXT_COMPONENT_STRING(string.format("%s",text));
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
