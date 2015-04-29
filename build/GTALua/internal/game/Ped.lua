-- Ped
class 'Ped'(Entity)

-- CTor
function Ped:__init(id)
	Entity.__init(self, id)
	
	self._type = "Ped"
end

-- Weapon Switching
function Ped:AllowWeaponSwitching(b)
	if b == nil then b = true end
	
	natives.PED.SET_PED_CAN_SWITCH_WEAPON(self.ID, b)
end

-- Weapon
function Ped:DelayedGiveWeapon(wep, ammo)
	if type(wep) == "string" then
		wep = natives.GAMEPLAY.GET_HASH_KEY(wep)
	end
	natives.WEAPON.GIVE_DELAYED_WEAPON_TO_PED(self.ID, wep, ammo, false)
end

-- Group Member
function Ped:AddGroupMember(other_ped)
	local group_id = other_ped
	print(type(other_ped))
	if type(other_ped) == "Ped" or type(other_ped) == "Player" then
		group_id = other_ped:GetGroupIndex()
	end
	natives.PED.SET_PED_AS_GROUP_MEMBER(self.ID, group_id)
end
function Ped:GetGroupIndex()
	return natives.PED.GET_PED_GROUP_INDEX(self.ID)
end