-- Vector
-- Vector + Vector
function Vector.__add(a, b)
	return Vector(a.x + b.x, a.y + b.y, a.z + b.z)
end

-- Vector - Vector
function Vector.__sub(a, b)
	return Vector(a.x - b.x, a.y - b.y, a.z - b.z)
end