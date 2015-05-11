-- Setup
function CScriptThread:internal_Timers_Setup()
	self.Timers = {}
	self.TimerIndex = 0
end

-- Add Timer
function CScriptThread:AddTimer(name, interval_ms, runs, callback, ...)
	name = name or "_unnamed_timer_"..self.TimerIndex
	table.insert(self.Timers, {
		Name = name ,
		Interval = interval_ms,
		NextRun = game.GetTime() + interval_ms,
		Runs = runs,
		Callback = callback,
		Arguments = {...}
	})
	self.TimerIndex = self.TimerIndex + 1
end

-- Cancel Timer
function CScriptThread:CancelTimer(name)
	for k,data in pairs(self.Timers) do
		if data.Name == name then
			table.remove(self.Timers, k)
			return true
		end
	end
	return false
end

-- Tick
function CScriptThread:internal_Timers_OnTick()
	for k,data in pairs(self.Timers) do
		if data.Runs == 0 then
			table.remove(self.Timers, k)
		elseif game.GetTime() >= data.NextRun then
			-- callback
			local success, err = pcall(function()
				if type(data.Callback) == "function" then
					data.Callback(unpack(data.Arguments))
				else
					self[data.Callback](self, unpack(data.Arguments))
				end
			end)
			
			-- error handling
			if not success then
				print("[Lua] ScriptThread "..self:GetName().." Timer Error: "..err)
			end
			
			-- update
			data.NextRun = game.GetTime() + data.Interval
			if data.Runs ~= -1 then
				data.Runs = data.Runs - 1
			end
		end
	end
end

-- Destroy
function CScriptThread:internal_Timers_Destroy()
	self.Timers = {}
	self.TimerIndex = 0
end