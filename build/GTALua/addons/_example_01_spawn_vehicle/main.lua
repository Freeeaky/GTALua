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
			
			-- Model Hash
			local model_hash = 0xC703DB5F -- 0xC703DB5F = Taxi
			
			-- Before we can use the model, we need to load it first
			-- Check if already loaded
			if not natives.STREAMING.HAS_MODEL_LOADED(model_hash) then
				-- Request Model
				natives.STREAMING.REQUEST_MODEL(model_hash)
				
				-- After you have requested the model, you need to wait until
				-- the model is actually loaded
				--
				-- For that we create another while-loop, make sure that you
				-- use self:IsRunning() again!
				while self:IsRunning() do
					-- Check if loaded
					if natives.STREAMING.HAS_MODEL_LOADED(model_hash) then
						-- Model has loaded, we can get out of the loop
						break
					end
					
					-- Wait
					self:Wait(1)
				end
			end
			-- The model is now loaded
			
			-- Create Vehicle
			natives.VEHICLE.CREATE_VEHICLE(model_hash, vec.x, vec.y, vec.z, 0.0, true, true)
			
			-- Set model as no longer needed
			-- Otherwise it lies around in memory
			natives.STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(model_hash)
		end
		
		-- Wait
		self:Wait(50)
	end
end
 
-- Register Thread
example_vehicle.Thread:Register()  