-- Vector
-- Vector + Vector
function Vector.__add(a, b)
	return Vector(a.x + b.x, a.y + b.y, a.z + b.z)
end

-- Vector - Vector
function Vector.__sub(a, b)
	return Vector(a.x - b.x, a.y - b.y, a.z - b.z)
end

-- Unpack
function Vector:Unpack()
	return self.x, self.y, self.z
end