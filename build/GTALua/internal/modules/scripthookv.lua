-- List of threads
scripthookv.ThreadList = {}

-- Types
scripthookv.TypeTable = {
	i = "number",
	f = "number",
	b = "boolean",
	s = "string",
	v = "void",
	V = "Vector",
	m = "CMemoryBlock",
	
	a = "number", -- any = int
	u = "number", -- unknown = int
}

-- Find Thread
function scripthookv.FindThread(name)
	return scripthookv.ThreadList[name]
end

-- Kill Thread
function scripthookv.KillThread(name)
	-- Find
	local thread = scripthookv.FindThread(name)
	if thread then
		thread:internal_Kill()
		scripthookv.ThreadList[name] = nil
	end
	
	-- Find in queue
	-- Needed for AutoRefresh (in case file reloads before init)
	for i,thread in pairs(scripthookv.RegisterThreadQueue) do
		if thread:GetName() == name then
			table.remove(scripthookv.RegisterThreadQueue, i)
		end
	end
end

-- Register Thread
function scripthookv.RegisterThread(thread, _noerror)
	if scripthookv.CanRegisterThreads() then
		scripthookv.internal_RegisterThread(thread)
		return true
	else
		if _noerror ~= true then
			error("You can no longer register threads! Make sure that your script registers your thread on startup!")
		end
		
		return false
	end
end