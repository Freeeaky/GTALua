--
-- Remember:
--   Your addon will only be loaded if you have an ASI file for it!
--   Take the empty_addon.asi, rename it, and copy it to your main GTA directory!
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