-- Entity class
class 'Entity'(Object)

-- CTor
function Entity:__init(id)
	self._type = "Entity"
	self.ID = id
end

-- Is*
function Entity:IsPed()
	self:_CheckExists()
	return natives.ENTITY.IS_ENTITY_A_PED(self.ID)
end
function Entity:IsVehicle()
	self:_CheckExists()
	return natives.ENTITY.IS_ENTITY_A_VEHICLE(self.ID)
end
function Entity:IsObject()
	self:_CheckExists()
	return natives.ENTITY.IS_ENTITY_AN_OBJECT(self.ID)
end

-- Misison Entities
function Entity:IsMissionEntity()
	self:_CheckExists()
	return natives.ENTITY.IS_ENTITY_A_MISSION_ENTITY(self.ID)
end
Entity.IsPersistant = Entity.IsMissionEntity
function Entity:SetMissionEntity(toggle)
	self:_CheckExists()
	natives.ENTITY.SET_ENTITY_AS_MISSION_ENTITY(self.ID, toggle or true, true)
end
Entity.SetPersistant = Entity.SetMissionEntity

-- Exists
function Entity:Exists()
	return natives.ENTITY.DOES_ENTITY_EXIST(self.ID)
end
function Entity:_CheckExists()
	if not self:Exists() then
		error("Entity is not valid!")
	end
end

-- Delete/Remove
function Entity:Delete()
	self:_CheckExists()
	local c_entity_handle = CMemoryBlock(4)
	c_entity_handle:WriteDWORD32(0, self.ID)
	natives.ENTITY.DELETE_ENTITY(c_entity_handle)
	c_entity_handle:Release()
end
Entity.Remove = function(s) return s:Delete() end

-- Position
function Entity:SetPosition(x, y, z)
	self:_CheckExists()

	if type(x) == "Vector" then
		z = x.z
		y = x.y
		x = x.x
	end
	
	natives.ENTITY.SET_ENTITY_COORDS(self.ID, x, y, z, false, false, false, true)
end
function Entity:GetPosition()
	self:_CheckExists()
	return natives.ENTITY.GET_ENTITY_COORDS(self.ID, false)
end
function Entity:GetOffsetVector(x,y,z)
	self:_CheckExists()
	if type(x) == "Vector" then
		z = x.z
		y = x.y
		x = x.x
	end
	
	return natives.ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self.ID, x, y, z)
end

-- Velocity
function Entity:SetVelocity(x, y, z)
	self:_CheckExists()
	if type(x) == "Vector" then
		z = x.z
		y = x.y
		x = x.x
	end
	
	natives.ENTITY.SET_ENTITY_VELOCITY(self.ID, x, y, z)
end
function Entity:GetVelocity()
	self:_CheckExists()
	return natives.ENTITY.GET_ENTITY_VELOCITY(self.ID)
end

-- Heading
function Entity:SetHeading(f)
	self:_CheckExists()
	natives.ENTITY.SET_ENTITY_HEADING(self.ID, f)
end
function Entity:GetHeading()
	self:_CheckExists()
	return natives.ENTITY.GET_ENTITY_HEADING(self.ID)
end

-- Freeze
function Entity:Freeze()
	self:_CheckExists()
	natives.ENTITY.FREEZE_ENTITY_POSITION(self.ID, true)
end
function Entity:UnFreeze()
	self:_CheckExists()
	natives.ENTITY.FREEZE_ENTITY_POSITION(self.ID, false)
end

-- Health
function Entity:SetHealth(h)
	self:_CheckExists()
	natives.ENTITY.SET_ENTITY_HEALTH(self.ID, h)
end
function Entity:GetHealth()
	self:_CheckExists()
	return natives.ENTITY.GET_ENTITY_HEALTH(self.ID)
end
function Entity:GetMaxHealth() 
	self:_CheckExists()
	return natives.ENTITY.GET_ENTITY_MAX_HEALTH(self.ID)
end
function Entity:IsDead()
	self:_CheckExists()
	return natives.ENTITY.IS_ENTITY_DEAD(self.ID)
end
function Entity:SetInvincible(b)
	self:_CheckExists()
	natives.ENTITY.SET_ENTITY_INVINCIBLE(self.ID, b)
end

-- Nearest Player
function Entity:GetNearestPlayer()
	self:_CheckExists()
	return natives.ENTITY.GET_NEAREST_PLAYER_TO_ENTITY(self.ID)
end

-- Visible
function Entity:IsVisible()
	self:_CheckExists()
	return natives.ENTITY.IS_ENTITY_VISIBLE(self.ID)
end
function Entity:SetVisible(b)
	self:_CheckExists()
	natives.ENTITY.SET_ENTITY_VISIBLE(self.ID,b)
end

-- Model
function Entity:GetModel()
	self:_CheckExists()
	return natives.ENTITY.GET_ENTITY_MODEL(self.ID)
end

-- Fire
function Entity:Ignite()
	self:_CheckExists()
	natives.FIRE.START_ENTITY_FIRE(self.ID)
end
function Entity:Extinguish()
	self:_CheckExists()
	natives.FIRE.STOP_ENTITY_FIRE(self.ID)
end

-- Blip
function Entity:AttachBlip()
	self:_CheckExists()
	local current_blip = self:GetBlip()
	if current_blip then
		return current_blip
	end
	return Blip(natives.UI.ADD_BLIP_FOR_ENTITY(self.ID))
end
function Entity:GetBlip()
	self:_CheckExists()
	local blip_id = natives.UI.GET_BLIP_FROM_ENTITY(self.ID)
	if blip_id > 0 then
		local blip = Blip(blip_id)
		if blip:Exists() then
			return blip
		end
	end
end