-- Entity class
class 'Entity'(Object)

-- CTor
function Entity:__init(id)
	--Object.__init(self, id)

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
function Entity:SetAsMissionEntity(toggle)
	self:_CheckExists()
	natives.ENTITY.SET_ENTITY_AS_MISSION_ENTITY(self.ID, toggle or true, true)
end
Entity.SetPersistant = Entity.SetAsMissionEntity

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
	natives.ENTITY.DELETE_ENTITY(self.ID)
end
Entity.Remove = Entity.Delete

-- Position
function Entity:SetPosition(x, y, z)
	self:_CheckExists()

	if type(x) == "Vector" then
		y = x.y
		z = x.z
		x = x.x
	end
	
	natives.ENTITY.SET_ENTITY_COORDS(self.ID, x, y, z, false, false, false, true)
end
function Entity:GetPosition()
	self:_CheckExists()
	return natives.ENTITY.GET_ENTITY_COORDS(self.ID, false)
end

-- Velocity
function Entity:SetVelocity(x, y, z)
	self:_CheckExists()
	if type(x) == "Vector" then
		x = x.x
		y = x.y
		z = x.z
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

-- Health
function Entity:SetHealth(h)
	self:_CheckExists()
	natives.ENTITY.SET_ENTITY_HEALTH(self.ID, h)
end
function Entity:GetHealth()
	self:_CheckExists()
	return natives.ENTITY.GET_ENTITY_HEALTH(self.ID)
end
function Entity:IsDead()
	self:_CheckExists()
	return natives.ENTITY.IS_ENTITY_DEAD(self.ID)
end
function Entity:SetInvincible(b)
	self:_CheckExists()
	natives.ENTITY.SET_ENTITY_INVINCIBLE(self.ID, b)
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