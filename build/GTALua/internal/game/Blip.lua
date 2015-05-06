-- Blip
class 'Blip'

-- CTor
function Blip:__init(handle)
	self.ID = handle
end

-- type & string
function Blip:__tostring()
	return "[Blip]"
end
function Blip:__type()
	return "Blip"
end

-- Exists
function Blip:Exists()
	return natives.UI.DOES_BLIP_EXIST(self.ID)
end
function Blip:_CheckExists()
	if not self:Exists() then
		error("Blip is not valid!")
	end
end

-- Delete
function Blip:Delete()
	self:_CheckExists()
	local c_blip = CMemoryBlock(4)
	c_blip:WriteDWORD32(0, self.ID)
	natives.UI.REMOVE_BLIP(c_blip)
	c_blip:Release()
end

-- Sprite
function Blip:SetSprite(i)
	self:_CheckExists()
	natives.UI.SET_BLIP_SPRITE(self.ID, i)
end
function Blip:GetSprite()
	self:_CheckExists()
	return natives.UI.GET_BLIP_SPRITE(self.ID)
end