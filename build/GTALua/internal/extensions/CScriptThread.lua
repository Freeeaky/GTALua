-- Script Thread CTOR
-- TODO: Move Reset to Register
function ScriptThread(name)
	-- I really hope people will find proper names for them..
	local existing_thread = scripthookv.FindThread(name)
	if existing_thread then
		existing_thread._Reset = true
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
	if self._Reset == true then
		self:Reset()
		self._Reset = nil
		return
	end
	if self:IsActive() then end
	
	-- Register
	local r = scripthookv.RegisterThread(self, true)
	if not r then
		error("ScriptThread:Register() failed - Has the Script Thread already been killed?")
	end
end

-- Tick function
function CScriptThread:Tick()
	if self.CoRoutine == nil then
		self:SetupCoroutine()
		self:Tick()
		return
	end
	if coroutine.status(self.CoRoutine) ~= "suspended" then
		print("Something is wrong with the coroutine!")
		--self:SetupCoroutine()
		--self:Tick()
		return
	end
	local status, err = coroutine.resume(self.CoRoutine)
	if not status then
		error(err)
	end
end

-- Setup CoRoutine
function CScriptThread:SetupCoroutine()
	self.CoRoutine = coroutine.create(function()
		return self:Run()
	end)
end