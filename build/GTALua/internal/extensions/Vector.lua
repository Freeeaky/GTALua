-- Vector
-- Vector + Vector
function Vector.__add(a, b)
	return Vector(a.x + b.x, a.y + b.y, a.z + b.z)
end

-- Vector - Vector
function Vector.__sub(a, b)
	return Vector(a.x - b.x, a.y - b.y, a.z - b.z)
end

-- Vector == Vector
function Vector.__eq(a, b)
	return a.x == b.x and a.y == b.y and a.z == b.z
end

-- Unpack
function Vector:Unpack()
	return self.x, self.y, self.z
end

-- Distance
function Vector:Distance(other_vec)
	local subvec = (self - other_vec)
	return math.sqrt(subvec.x * subvec.x + subvec.y * subvec.y + subvec.z * subvec.z)
end
