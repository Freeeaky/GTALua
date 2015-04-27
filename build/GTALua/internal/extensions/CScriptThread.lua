-- Script Thread CTOR
function ScriptThread(name)
	-- Reset thread with same name
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
	scripthookv.RegisterThread(self)
end