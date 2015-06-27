-- Ped
class 'Ped'(Entity)

-- CTor
function Ped:__init(id)
	Entity.__init(self, id)
	
	self._type = "Ped"
end

-- Delete
function Ped:Delete()
	self:_CheckExists()
	local c_handle = CMemoryBlock(4)
	c_handle:WriteDWORD32(0, self.ID)
	natives.PED.DELETE_PED(c_handle)
	c_handle:Release()
end

-- Weapon Switching
function Ped:AllowWeaponSwitching(b)
	self:_CheckExists()
	if b == nil then b = true end
	
	natives.PED.SET_PED_CAN_SWITCH_WEAPON(self.ID, b)
end

-- Weapon
function Ped:DelayedGiveWeapon(wep, ammo)
	self:_CheckExists()
	if type(wep) == "string" then
		wep = natives.GAMEPLAY.GET_HASH_KEY(wep)
	end
	natives.WEAPON.GIVE_DELAYED_WEAPON_TO_PED(self.ID, wep, ammo, false)
end

function Ped:RemoveWeapon(wep)
	self:_CheckExists()
	if type(wep) == "string" then
		wep = natives.GAMEPLAY.GET_HASH_KEY(wep)
	end
	natives.WEAPON.REMOVE_WEAPON_FROM_PED(self.ID, wep)
end

function Ped:RemoveAllWeapons()
	natives.WEAPON.REMOVE_ALL_PED_WEAPONS(self.ID, true)
end

-- Group Member
function Ped:AddGroupMember(other_ped)
	self:_CheckExists()
	local group_id = other_ped
	if type(other_ped) == "Ped" or type(other_ped) == "Player" then
		group_id = other_ped:GetGroupIndex()
	end
	natives.PED.SET_PED_AS_GROUP_MEMBER(self.ID, group_id)
end
function Ped:GetGroupIndex()
	self:_CheckExists()
	return natives.PED.GET_PED_GROUP_INDEX(self.ID)
end

-- Vehicle
function Ped:IsInVehicle()
	self:_CheckExists()
	return natives.PED.IS_PED_IN_ANY_VEHICLE(self.ID, false)
end
function Ped:GetVehicle()
	self:_CheckExists()
	if self:IsInVehicle() then
		local veh = natives.PED.GET_VEHICLE_PED_IS_IN(self.ID, false)
		return Vehicle(veh)
	end
end

-- Armour
function Ped:SetArmour(i)
	self:_CheckExists()
	natives.PED.SET_PED_ARMOUR(self.ID, i)
end
Ped.SetArmor = Ped.SetArmour
function Ped:GetArmour(i)
	self:_CheckExists()
	return natives.PED.GET_PED_ARMOUR(self.ID, i)
end
Ped.GetArmor = Ped.GetArmour

-- Nearby Peds
function Ped:GetNearbyPeds(max_peds)
	self:_CheckExists()
	
	-- default value
	if max_peds == nil then
		-- lets just put a high number in here for now
		max_peds = 100
	end
	
	-- c array
	local array_size = 2 * max_peds + 2
	local c_array_peds = CMemoryBlock(array_size * 4)
	
	-- index 0 defines the length of the array
	c_array_peds:WriteInt32(0, max_peds)

	-- call native
	natives.PED.GET_PED_NEARBY_PEDS(self.ID, c_array_peds, -1)
	
	-- check returned peds
	local nearby_peds = {}
	for offset = 4, array_size, 4 do
		local ped = Ped(c_array_peds:ReadDWORD32(offset))
		if ped:Exists() then
			table.insert(nearby_peds, ped)
		end
	end
	
	-- release
	c_array_peds:Release()
	return nearby_peds
end

-- Nearby Vehicles
function Ped:GetNearbyVehicles(max_vehicles)
	self:_CheckExists()
	
	-- default value
	if max_vehicles == nil then
		max_vehicles = 50
	end
	
	-- c array
	local array_size = 2 * max_vehicles + 2
	local c_array_vehicles = CMemoryBlock(array_size * 4)
	c_array_vehicles:WriteInt32(0, max_vehicles)
	
	-- call native
	natives.PED.GET_PED_NEARBY_VEHICLES(self.ID, c_array_vehicles)
	
	-- check
	local nearby_vehicles = {}
	for offset = 4, array_size, 4 do
		local veh = Vehicle(c_array_vehicles:ReadDWORD32(offset))
		if veh:Exists() then
			table.insert(nearby_vehicles, veh)
		end
	end
	
	-- release
	c_array_vehicles:Release()
	return nearby_vehicles
end
