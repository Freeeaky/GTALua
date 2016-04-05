-- GUI
gui = {}

-- Fonts:
-- 0: Arial http://puu.sh/hA0Kj/ab70130bcf.png
-- 1: GTA Font http://puu.sh/hA0LS/91bf31e5d1.png
-- 2: All Uppercased http://puu.sh/hA0Nt/99ef146a53.png
-- 3: Symbols http://puu.sh/hA0RK/761968e61e.png
-- 4: Normal Font http://puu.sh/hA0SP/6f7e19cd70.png
-- 5: /

-- Color
function Color(r, g, b, a)
	return
	{
		r = r,
		g = g,
		b = b,
		a = a or 255,
		
		Unpack = function(s)
			return s.r, s.g, s.b, s.a
		end
	}
end

-- Rect
function gui.DrawRect(a, b, c, d, col)
	natives.GRAPHICS.DRAW_RECT(a + (c * 0.5), b + (d * 0.5), c, d, col.r, col.g, col.b, col.a)
end

-- Text
function gui.DrawText(x, y, text, tbl)
	tbl = tbl or {}
	
	natives.UI.SET_TEXT_FONT(tbl.Font or 1)
	natives.UI.SET_TEXT_SCALE(0, tbl.TextScale or 0.5)
	natives.UI.SET_TEXT_COLOUR((tbl.Color or Color(255,255,255)):Unpack())
	natives.UI.SET_TEXT_CENTRE(tbl.Centered or false)
	if tbl.DropShadow then
		natives.UI.SET_TEXT_DROPSHADOW(unpack(tbl.DropShadow))
	else
		natives.UI.SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0)
	end
	if tbl.TextEdge then
		natives.UI.SET_TEXT_EDGE(unpack(tbl.TextEdge))
	else
		natives.UI.SET_TEXT_EDGE(0, 0, 0, 0, 0)
	end
	natives.UI._SET_TEXT_ENTRY("STRING")
	natives.UI.ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text)
	natives.UI._DRAW_TEXT(x, y)
end

-- Beep
function gui.BeepNavUpDown()
	natives.AUDIO.PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false)
end
function gui.BeepSelect()
	natives.AUDIO.PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false)
end
function gui.BeepBack()
	natives.AUDIO.PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false)
end

-- Notify Above Map
function gui.NotifyAboveMap(text, blink)
	if blink == nil or type(blink) ~= "boolean" then
		blink = false
	end

	natives.UI._SET_NOTIFICATION_TEXT_ENTRY("STRING")
	natives.UI.ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text)
	natives.UI._DRAW_NOTIFICATION(blink, true)
end

-- Subtitle
function gui.Subtitle(text, duration)
	natives.UI._SET_TEXT_ENTRY_2("STRING")
	natives.UI.ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text)
	natives.UI._DRAW_SUBTITLE_TIMED(duration or 2000, true)
end

-- Prompt
function gui.Prompt(title, placeholder, max_lenght)
	natives.GAMEPLAY.DISPLAY_ONSCREEN_KEYBOARD(true, title or "", "", placeholder or "", "", "", "", ((max_lenght or 255) + 1))
	while (natives.GAMEPLAY.UPDATE_ONSCREEN_KEYBOARD() == 0) do coroutine.yield() end

	-- if user exit prompt without confirming : return placeholder
	if not natives.GAMEPLAY.GET_ONSCREEN_KEYBOARD_RESULT() then return placeholder end

	return natives.GAMEPLAY.GET_ONSCREEN_KEYBOARD_RESULT()
end

include("gui/simple_menu.lua")
