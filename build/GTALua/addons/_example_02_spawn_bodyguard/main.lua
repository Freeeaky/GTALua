--
-- Check out our the Wiki!
--     http://freeschi.com/w/index.php/Main_Page
--     http://freeschi.com/w/index.php/Getting_Started
--     http://freeschi.com/w/index.php/API
--

-- I recommend matching addon name & script thread name
example_spawn_bodyguard = ScriptThread("example_02_spawn_bodyguard") 

-- Run function
function example_spawn_bodyguard:Run()
	while self:IsRunning() do
		-- Key-Check
		if IsKeyDown(KEY_F9) then
			-- Delete old Bodyguard
			if self.LastBodyguard ~= nil and self.LastBodyguard:Exists() then
				self.LastBodyguard:Delete()
			end
			
			-- Player Position
			local player_pos = LocalPlayer():GetPosition()
			
			-- Load Model
			local model_hash = 0x4D6DE57E -- priest
			streaming.RequestModel(model_hash)
			
			-- Spawn ped
			local ped = game.CreatePed(model_hash, player_pos)
			self.LastBodyguard = ped
			
			-- Now we can give the character certain properties
			-- Weapons
			ped:AllowWeaponSwitching(true)
			ped:DelayedGiveWeapon("WEAPON_PISTOL", 1000)
			
			-- Group Member / Bodyguard
			ped:AddGroupMember(LocalPlayer())
			
			-- Set model as no longer needed
			streaming.ReleaseModel(model_hash)
		end
		
		-- Wait
		self:Wait(50)
	end
end

-- OnError
function example_spawn_bodyguard:OnError()
	-- Read Tutorial 1 to find out what this does
	print("Oh no! Example Thread caused an error!")
	self:Reset()
end
 
-- Register
example_spawn_bodyguard:Register()  