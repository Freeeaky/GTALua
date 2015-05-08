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