-- Includes
include("modules/event.lua")
include("modules/natives.lua")


-- Test
--[[thread = ScriptThread()

function thread:OnRun()
	-- set time to 8:00:00
	natives.time.SetClockTime:Call(8,0,0)
	
	-- player ped id
	local localplayer = natives.player.GetPlayerPed:Call(-1)
	
	if natives.entity.DoesEntityExist:Call(localplayer) then
		local vec = natives.entity.GetEntityCoords:Call(localplayer)
		
		--[[-- request model
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
			print("create at ", vec.x, " ", vec.y, " ", vec.z)
			local r = natives.vehicle.CreateVehicle:Call(0x2B6DC64A, vec.x, vec.y + 2, vec.z, 0.0, true, true)
			print(r)
		end]]
		
		local vehicle_hash = 0xC703DB5F
		
		if IsKeyCurrentlyDown(0x78) then
			if not self.WasF9Pressed then
				--local r = natives.streaming.RequestModel:Call(vehicle_hash)
				--print("Model requested: ", r)
				self.WasF9Pressed = true
				self.IsWaitingForModel = true
			end
		else
			self.WasF9Pressed = false
		end
		
		if self.IsWaitingForModel then
			if natives.streaming.HasModelLoaded:Call(vehicle_hash) then
				print("create at ", vec.x, " ", vec.y, " ", vec.z)
				local r = natives.vehicle.CreateVehicle:Call(vehicle_hash, vec.x, vec.y + 2, vec.z, 0.0, true, false)
				print("1: ", r)
				
				self.IsWaitingForModel = false
				self.WasF9Pressed = true
			end
		end
	end
end

event.AddListener("OnScriptEngineInitialized", "test_thread", function()
	thread.WasF9Pressed = true
	thread.IsWaitingForModel = false
	engine.RegisterScriptThread(thread)
end)

console.Log("Testing !...")]]