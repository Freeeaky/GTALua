-- Object class
class 'Object'

-- CTor
function Object:__init(id)
	self._type = "Object"
	self.ID = id
end

-- __type
function Object:__type()
	return self._type
end