-- test_script
local thread = ScriptThread("test_script")

print("h")

-- Run
function thread:Run()
	print("test_script:Run")
	
	while self:IsRunning() do
		-- Spawn Taxi
		if IsKeyDown(0x78) then -- F9
			-- Note: Taxi model is always loaded, no need to load it first
			local localplayer = natives.PLAYER.GET_PLAYER_PED(-1)
			local vec = natives.ENTITY.GET_ENTITY_COORDS(localplayer, true)
			natives.VEHICLE.CREATE_VEHICLE(0xC703DB5F, vec.x, vec.y, vec.z, 0.0, true, true)
		end
		
		-- Wait
		self:Wait(50)
	end
	
	print("oh no!")
end

print("HELLO MATE ?")
 
-- Register Thread
thread:Register()  