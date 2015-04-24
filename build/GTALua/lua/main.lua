-- Includes
include("modules/event.lua")
include("modules/natives.lua")

-- Test
thread = ScriptThread()

function thread:OnRun()
	-- set time to 8:00:00
	natives.time.SetClockTime:Call(8,0,0)
	
	-- player ped id
	local localplayer = natives.player.GetPlayerPed:Call(-1)
	
	if localplayer > 100 then
		local vec = natives.entity.GetEntityCoords:Call(localplayer)
		
		-- request model
		self.ModelLoaded = natives.streaming.HasModelLoaded:Call(0x2B6DC64A)
		if not self.ModelLoaded and not self.ModelRequested then
			natives.streaming.RequestModel:Call(0x2B6DC64A)
			self.ModelRequested = true
		end
		if self.ModelLoaded then
			self.ModelRequested = false
		end
		
		-- wait for model
		if self.ModelLoaded and IsKeyCurrentlyDown(0x78) then
			-- not working yet
			-- IsKeyCurrentlyDown not working atm
			natives.vehicle.CreateVehicle:Call(0x2B6DC64A, vec, 0.0, false, false)
		end
	end
end

event.AddListener("OnScriptEngineInitialized", "test_thread", function()
	thread.ModelLoaded = false
	thread.ModelRequested = false
	engine.RegisterScriptThread(thread)
end)

console.Log("Testing !...")