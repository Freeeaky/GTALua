-- Vehicle
class 'Vehicle'(Entity)

-- CTor
function Vehicle:__init(id)
	Entity.__init(self, id)
	
	self._type = "Vehicle"
end

-- Is vehicle stuck on roof (returns true/false)
function Vehicle:IsStuckOnRoof()
	self:_CheckExists()
	return natives.VEHICLE.IS_VEHICLE_STUCK_ON_ROOF(self.ID)
end

-- Returns amount of passengers in vehicle
function Vehicle:NumberOfPassengers()
	self:_CheckExists()
	return natives.VEHICLE.GET_VEHICLE_NUMBER_OF_PASSENGERS(self.ID)
end

-- Returns max number of passengers
function Vehicle:MaxNumberOfPassengers()
	self:_CheckExists()
	return natives.VEHICLE.GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(self.ID)
end