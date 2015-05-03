-- Vehicle
class 'Vehicle'(Entity)

-- CTor
function Vehicle:__init(id)
	Entity.__init(self, id)
	
	self._type = "Vehicle"
end