-- Timer
-- This is more or less just a wrapper for the Timer function in CScriptThread
timer = {}

-- Simple
-- Runs once, cannot be cancelled!
function timer.Simple(ms, callback, ...)
	return timer.Create(nil, ms, 1, callback, unpack({...}))
end

-- Create
-- Make sure name is unique
-- runs = -1 => unlimited runs
function timer.Create(name, ms, runs, callback, ...)
	-- Thread
	if scripthookv.ActiveThread == nil then
		error("timer.Simple failed! Unknown active thread! Has this been called outside of a thread?")
	end
	
	-- Add
	return scripthookv.ActiveThread:AddTimer(name, ms, runs, callback, unpack({...}))
end

-- Cancel
function timer.Cancel(name)
	-- Thread
	if scripthookv.ActiveThread == nil then
		error("timer.Simple failed! Unknown active thread! Has this been called outside of a thread?")
	end
	
	-- Cancel
	return scripthookv.ActiveThread:CancelTimer(name)
end