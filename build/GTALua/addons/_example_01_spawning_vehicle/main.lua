-- Setup a table where we put all our values
example_vehicle = {}

-- Create a ScriptThread
-- Make sure you have a unique name for your thread!
example_vehicle.Thread = ScriptThread("example_spawn_vehicle") 

-- Run function
-- This is called once! It's your job to keep this alive!
function example_vehicle.Thread:Run()
	-- while-loop, do not use while true !
	while self:IsRunning() do
		-- Key-Down-Check, 0x78 = F9
		-- You can look up key codes in Google ("virtual key codes")
		if IsKeyDown(0x78) then
			-- Get Local Player Ped
			-- -1 is always the ID for the local player
			local local_player_ped = natives.PLAYER.GET_PLAYER_PED(-1)
			
			-- Get Entity Position
			-- entity = local_player_ped
			local vec = natives.ENTITY.GET_ENTITY_COORDS(local_player_ped, true)
			-- This function returns a vector
			-- You can access vec.x vec.y and vec.z for the coordinates
			
			-- Create Vehicle
			-- 0xC703DB5F is the model hash for the taxi
			-- Note: Taxi model is always loaded, no need to load it first
			natives.VEHICLE.CREATE_VEHICLE(0xC703DB5F, vec.x, vec.y, vec.z, 0.0, true, true)
		end
		
		-- Wait
		self:Wait(50)
	end
end
 
-- Register Thread
example_vehicle.Thread:Register()  