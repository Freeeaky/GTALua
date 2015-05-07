--
-- Check out "Getting started" on the Wiki!
--     http://freeschi.com/w/index.php/Main_Page
--     http://freeschi.com/w/index.php/Getting_Started
--

-- Create a ScriptThread
-- I recommend matching addon name & script thread name
example_vehicle = ScriptThread("example_01_spawn_vehicle") 

-- Run function
-- This is called once! It's your job to keep this alive!
function example_vehicle:Run()
	print("hi")
	
	-- while-loop, do not use while true !
	while self:IsRunning() do
		-- Key-Down-Check
		if IsKeyDown(KEY_F9) then
			-- Local Player Position
			local player_pos = LocalPlayer():GetPosition()

			-- Load Model
			streaming.RequestModel(VEHICLE_TAXI)
			
			-- Create Vehicle
			game.CreateVehicle(VEHICLE_TAXI, player_pos)
			
			-- Set model as no longer needed
			-- Otherwise it lies around in memory
			streaming.ReleaseModel(VEHICLE_TAXI)
		end
		
		-- Wait
		self:Wait(50)
	end
end

-- OnError
function example_vehicle:OnError()
	-- If :Run causes an error, this function is called
	-- You have 3 options here
	-- -> 1: Reset
	--       The :Run function is ran again
	-- -> 2: Kill
	--       This will Kill the thread ->completely<-
	--       After that you'll not be able to restart the thread
	-- -> 3: Do Nothing
	--       The thread will be kept alive
	--       You are able to restart the thread with reload_addon
	--
	-- I recommend that you keep the thread alive (option 1/3)
	-- because if you Kill it, you can no longer work with it!
	print("Oh no! Example Thread caused an error!")
	self:Reset()
end
 
-- Register Thread
example_vehicle:Register()