-- Object class
class 'Object'(Entity)

-- CTor
function Object:__init(id)
	Entity.__init(self, id)
	
	self._type = "Object"
end

-- Delete
function Object:Delete()
	self:_CheckExists()
	local c_handle = CMemoryBlock(4)
	c_handle:WriteDWORD32(0, self.ID)
	natives.OBJECT.DELETE_OBJECT(c_handle)
	c_handle:Release()
end

--Set not needed
function Object:SetNotNeeded()
	self:_CheckExists()
	local c_object_handle = CMemoryBlock(4)
	c_object_handle:WriteDWORD32(0, self.ID)
	natives.ENTITY.SET_OBJECT_AS_NO_LONGER_NEEDED(c_object_handle)
	c_object_handle:Release()
end
