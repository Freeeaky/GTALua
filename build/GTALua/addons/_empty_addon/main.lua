--
-- Check out "Getting started" on the Wiki!
--     http://freeschi.com/w/index.php/Main_Page
--     http://freeschi.com/w/index.php/Getting_Started
--     http://freeschi.com/w/index.php/API
--

-- Please rename empty_addon!
empty_addon = ScriptThread("empty_addon")

-- Run
function empty_addon:Run()
	while self:IsRunning() do
		-- Do your magic here
		
		-- Wait
		self:Wait(50)
	end
end

-- OnError
function empty_addon:OnError()
	print("empty_addon Thread caused an error!")
	self:Reset()
end

-- Register
empty_addon:Register()