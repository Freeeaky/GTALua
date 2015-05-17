--
-- Check out our the Wiki!
--     http://wiki.gtalua.com/index.php/Main_Page
--     http://wiki.gtalua.com/index.php/Getting_Started
--     http://wiki.gtalua.com/index.php/API
--
-- I recommend matching addon name & script thread name
example_events = ScriptThread("example_05_events")

-- OnPedCreated Handler
function example_events:EventHandler_PedCreated(ped_id)	
	-- Only touch the entity shortly later!
	-- It might be instantly deleted again from a game script
	timer.Simple(200, function()
		-- Note: an ID is passed! not a Ped class
		local ped = Ped(ped_id)
		
		-- Always make sure that it exists
		if not ped:Exists() then return end
		
		-- Add Blip for them
		ped:AttachBlip()
	end)
end

-- OnVehicleCreated Handler
function example_events:EventHandler_VehicleCreated(vehicle_id)
	timer.Simple(2000, function()
		local vehicle = Vehicle(vehicle_id)
		if not vehicle:Exists() then return end
		
		-- Blip
		vehicle:AttachBlip()
		
		-- Neon Lights
		vehicle:SetNeonLights(true, math.random(0,255), math.random(0,255), math.random(0,255))
	end)
end

-- Run
function example_events:Run()
	-- Add Handler
	example_events:AddEventHandler("OnPedCreated", "EventHandler_PedCreated")
	example_events:AddEventHandler("OnVehicleCreated", "EventHandler_VehicleCreated")
end

-- Register
example_events:Register()