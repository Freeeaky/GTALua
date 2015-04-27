-- Script Thread CTOR
function ScriptThread(name)
	-- Kill thread with same name
	local existing_thread = scripthookv.FindThread(name)
	if existing_thread then
		existing_thread:Kill()
		scripthookv.ThreadList[name] = nil
	end
	
	-- Create new
	scripthookv.ThreadList[name] = CScriptThread(name)
	return scripthookv.ThreadList[name]
end

-- Kill Thread
function CScriptThread:Kill()
	scripthookv.FindThread(self:GetName())
end

-- Register Thread
function CScriptThread:Register()
	scripthookv.RegisterThread(self)
end