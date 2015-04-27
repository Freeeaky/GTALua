-- List of threads
scripthookv.ThreadList = {}

-- Find Thread
function scripthookv.FindThread(name)
	return scripthookv.ThreadList[name]
end

-- Kill Thread
function scripthookv.KillThread(name)
	local thread = scripthookv.FindThread(name)
	if thread then
		thread:internal_Kill()
		scripthookv.ThreadList[name] = nil
	end
end

-- Register Thread
scripthookv.RegisterThreadQueue = {}
function scripthookv.RegisterThread(thread)
	if not scripthookv.IsInitialized() then
		table.insert(scripthookv.RegisterThreadQueue, thread)
	else
		scripthookv.internal_RegisterThread(thread)
	end
end

-- Thread Queue
event.AddListener("OnScriptEngineInitialized", "internal_RegisterQueuedThreads", function()
	-- Register queued threads
	-- scripthookv.RegisterThread is now safe since the script engine is initialized
	for _,thread in pairs(scripthookv.RegisterThreadQueue) do
		scripthookv.RegisterThread(thread)
	end
end)