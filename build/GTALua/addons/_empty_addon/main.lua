--
-- Check out our the Wiki!
--     http://wiki.gtalua.com/index.php/Main_Page
--     http://wiki.gtalua.com/index.php/Getting_Started
--     http://wiki.gtalua.com/index.php/API
--

-- Please rename empty_addon!
-- I recommend matching thread name & folder name!
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