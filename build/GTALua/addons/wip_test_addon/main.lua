include("../../internal/extensions/CNativeReg.lua")
example_spawn_bodyguard = ScriptThread("example_spawn_bodyguard") 

-- Run function
function example_spawn_bodyguard:Run()
	while self:IsRunning() do
		-- Key-Check
		if IsKeyDown(KEY_F9) then			
			local nearby_peds = LocalPlayer():GetNearbyPeds()
			for _,ped in pairs(nearby_peds) do
				ped:Ignite()
			end
			
			--error("shit")
			--[[if true then return true end
			local vec = natives.ENTITY.GET_ENTITY_COORDS(local_player_ped, true)
			
			-- Load Model
			-- This was explained in example 1
			local model_hash = 0x4D6DE57E -- 0x4D6DE57E = priest
			if not natives.STREAMING.HAS_MODEL_LOADED(model_hash) then
				natives.STREAMING.REQUEST_MODEL(model_hash)
				
				while self:IsRunning() do
					if natives.STREAMING.HAS_MODEL_LOADED(model_hash) then
						break
					end
					self:Wait(1)
				end
			end
			
			-- Spawn ped
			local ped_handle = natives.PED.CREATE_PED(26, model_hash, vec.x, vec.y, vec.z, 0, true, true)
			
			-- Now we can give the character certain properties
			-- Weapons
			natives.PED.SET_PED_CAN_SWITCH_WEAPON(ped_handle, true)
			local hk = natives.GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL")
			natives.WEAPON.GIVE_DELAYED_WEAPON_TO_PED(ped_handle, hk, 1000, false)
			
			-- Group Member / Bodyguard
			local player_group_id = natives.PED.GET_PED_GROUP_INDEX(local_player_ped)
			natives.PED.SET_PED_AS_GROUP_MEMBER(ped_handle, player_group_id)
			
			-- Set model as no longer needed
			natives.STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(model_hash)]]
		end
		
		-- Wait
		self:Wait(50)
	end
end

-- OnError
function example_spawn_bodyguard:OnError()
	-- Read Tutorial 1 to find out what this does
	print("Oh no! Example Thread caused an error!")
	--self:Reset()
end
 
-- Register
example_spawn_bodyguard:Register()  