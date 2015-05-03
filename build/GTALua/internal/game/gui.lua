-- GUI
gui = {}

-- Color
function Color(r, g, b, a)
	return
	{
		r = r,
		g = g,
		b = b,
		a = a or 255
	}
end

-- Rect
function gui.DrawRect(x1, x2, y1, y2, col)
	natives.GRAPHICS.DRAW_RECT(x1, x2, y1, y2, col.r, col.g, col.b, col.a)
end

-- Button
function gui.DrawButton()
	--
end