-- Vehicle
class 'Vehicle'(Entity)

-- CTor
function Vehicle:__init(id)
	Entity.__init(self, id)
	
	self._type = "Vehicle"
end

-- Delete
function Vehicle:Delete()
	self:_CheckExists()
	local c_handle = CMemoryBlock(4)
	c_handle:WriteDWORD32(0, self.ID)
	natives.VEHICLE.DELETE_VEHICLE(c_handle)
	c_handle:Release()
end

-- Is vehicle stuck on roof (returns true/false)
function Vehicle:IsStuckOnRoof()
	self:_CheckExists()
	return natives.VEHICLE.IS_VEHICLE_STUCK_ON_ROOF(self.ID)
end

-- Returns amount of passengers in vehicle
function Vehicle:GetNumberOfPassengers()
	self:_CheckExists()
	return natives.VEHICLE.GET_VEHICLE_NUMBER_OF_PASSENGERS(self.ID)
end

-- Returns max number of passengers
function Vehicle:GetMaxNumberOfPassengers()
	self:_CheckExists()
	return natives.VEHICLE.GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(self.ID)
end

-- Explode vehicle
function Vehicle:Explode()
	self:_CheckExists()
	natives.VEHICLE.EXPLODE_VEHICLE(self.ID, true, true)
end

-- Set primary colour.
function Vehicle:SetPrimaryColour(r, g, b)
	self:_CheckExists()
	natives.VEHICLE.SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(self.ID,r,g,b)
end

-- Set secondary colour.
function Vehicle:SetSecondaryColour(r, g, b)
	self:_CheckExists()
	natives.VEHICLE.SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(self.ID,r,g,b)
end

-- Checks whether the vehicle siren is on.
function Vehicle:IsSirenOn()
	self:_CheckExists()
	return natives.VEHICLE.IS_VEHICLE_SIREN_ON(self.ID)
end

-- Checks the vehicles dirt level
function Vehicle:GetDirtlevel()
	self:_CheckExists()
	return natives.VEHICLE.GET_VEHICLE_DIRT_LEVEL(self.ID)
end

-- Sets the vehicles dirt level (0 = clean, 15 = dirty)
function Vehicle:SetDirtLevel(i)
	self:_CheckExists()
	natives.VEHICLE.SET_VEHICLE_DIRT_LEVEL(self.ID,i)
end

-- Sets whether the vehicle engine is on.
function Vehicle:SetEngineState(b)
	self:_CheckExists()
	natives.VEHICLE.SET_VEHICLE_ENGINE_ON(self.ID,b,true)
end

-- Checks whether the vehicle is on all wheels
function Vehicle:IsOnAllWheels()
	self:_CheckExists()
	return natives.VEHICLE.IS_VEHICLE_ON_ALL_WHEELS(self.ID)
end

-- Fixes the vehicle
function Vehicle:Fix()
	self:_CheckExists()
	natives.VEHICLE.SET_VEHICLE_FIXED(self.ID)
end

-- Neon Lights
function Vehicle:SetNeonLights(enabled, r, g, b, location)
	self:_CheckExists()
	
	-- on/off
	if location == nil then
		natives.VEHICLE.SET_VEHICLE_NEON_LIGHTS_ON(self.ID, 0, enabled)
		natives.VEHICLE.SET_VEHICLE_NEON_LIGHTS_ON(self.ID, 1, enabled)
		natives.VEHICLE.SET_VEHICLE_NEON_LIGHTS_ON(self.ID, 2, enabled)
		natives.VEHICLE.SET_VEHICLE_NEON_LIGHTS_ON(self.ID, 3, enabled)
	else
		natives.VEHICLE.SET_VEHICLE_NEON_LIGHTS_ON(self.ID, location, enabled)
	end
	
	-- color
	if r == nil then return end
	if type(r) == "table" then
		b = r.b
		g = r.g
		r = r.r
	end
	natives.VEHICLE.SET_VEHICLE_NEON_LIGHTS_COLOUR(self.ID, r, g, b)
end

-- Plate function
function Vehicle:GetPlateType()
	self:_CheckExists()
	return natives.VEHICLE.GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(self.ID)
end
function Vehicle:SetPlateType(i)
	self:_CheckExists()
	natives.VEHICLE.SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(self.ID, i)
end

function Vehicle:GetPlateText()
	self:_CheckExists()
	return natives.VEHICLE.GET_VEHICLE_NUMBER_PLATE_TEXT(self.ID)
end
function Vehicle:SetPlateText(text)
	self:_CheckExists()
	natives.VEHICLE.SET_VEHICLE_NUMBER_PLATE_TEXT(self.ID, text)
end
