example_spawn_ped = {}
example_spawn_ped.Thread = ScriptThread("example_spawn_ped") 

-- Run function
function example_spawn_ped.Thread:Run()
	while self:IsRunning() do
		-- F9
		if IsKeyDown(0x78) then
			local local_player_ped = natives.PLAYER.GET_PLAYER_PED(-1)
			local vec = natives.ENTITY.GET_ENTITY_COORDS(local_player_ped, true)
			
			-- Model Hash
			local model_hash = 0x4D6DE57E -- 0x4D6DE57E = priest
			
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
			-- Spawn our ped
			natives.PED.CREATE_PED(26, model_hash, vec.x, vec.y, vec.z, 0, true, true)
		end
		
		-- Wait
		self:Wait(50)
	end
end
 
-- Register Thread
example_spawn_ped.Thread:Register()  