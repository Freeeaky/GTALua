-- Script Thread CTOR
-- TODO: Move Reset to Register
function ScriptThread(name)
	
end

-- Kill Thread
function CScriptThread:Kill()
	
end

-- Register Thread
function CScriptThread:Register()
	-- AutoRefresh
	if self:IsActive() then return end
	
	-- Register
end