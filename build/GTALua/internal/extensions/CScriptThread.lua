-- Script Thread CTOR
function ScriptThread(name)
	-- I really hope people will find proper names for them..
	local existing_thread = scripthookv.FindThread(name)
	if existing_thread then
		existing_thread._Reset = true
		existing_thread:internal_EventHandlers_Destroy()
		return scripthookv.ThreadList[name]
	end
	
	-- Create new
	scripthookv.ThreadList[name] = CScriptThread(name)
	scripthookv.ThreadList[name]:internal_Setup()
	return scripthookv.ThreadList[name]
end

-- Setup
function CScriptThread:internal_Setup()
	-- Event Handler
	self:internal_EventHandlers_Setup()
end

-- String/Type
function CScriptThread:__tostring()
	return "[CScriptThread "..self:GetName().."]"
end
function CScriptThread:__type()
	return "CScriptThread"
end

-- Kill Thread
function CScriptThread:Kill()
	-- Event Handlers
	self:internal_EventHandlers_Destroy()
	
	-- Kill
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
	local thread_type = scripthookv.RegisterThread(self)
	if thread_type == -1 then return end
	
	-- Add to main thread if it doesn't have its own thread
	if thread_type == 1 then
		scripthookv.FindThread("main_thread"):AddThread(self)
	end
end

-- internal: Tick
function CScriptThread:internal_OnTick()
	-- Setup CoRoutine for :Run
	if self.CoRoutine == nil then
		self:SetupCoroutine()
		self:Tick()
		return
	end
	
	-- Event Handlers
	self:internal_EventHandlers_OnTick()
	
	-- OnTick
	self:OnTick()
end

-- Tick function
function CScriptThread:Tick()	
	-- Check Status
	if coroutine.status(self.CoRoutine) ~= "suspended" then
		if self.QuitMessage == nil then
			print("[LuaScriptThread] Thread "..self:GetName().." quit")
			self.QuitMessage = true
		end
		return
	end
	
	-- Resume
	local status, err = coroutine.resume(self.CoRoutine)
	
	-- Report errors
	if not status then
		print("[LUA] "..err)
		print(debug.traceback(self.CoRoutine, err))
	end
end

-- Setup CoRoutine
function CScriptThread:SetupCoroutine()
	self.QuitMessage = nil
	self.CoRoutine = coroutine.create(function()
		return self:Run()
	end)
end