-- Script Thread CTOR
-- TODO: Move Reset to Register
function ScriptThread(name)
	-- Reset thread with same name
	-- I really hope people will find proper names for them..
	local existing_thread = scripthookv.FindThread(name)
	if existing_thread then
		existing_thread:Reset()
		return scripthookv.ThreadList[name]
	end
	
	-- Create new
	scripthookv.ThreadList[name] = CScriptThread(name)
	return scripthookv.ThreadList[name]
end

-- Kill Thread
function CScriptThread:Kill()
	scripthookv.KillThread(self:GetName())
end

-- Register Thread
function CScriptThread:Register()
	-- AutoRefresh
	if self:IsActive() then return end
	
	-- Register
	local r = scripthookv.RegisterThread(self, true)
	if not r then
		error("ScriptThread:Register() failed - Has the Script Thread already been killed?")
	end
end