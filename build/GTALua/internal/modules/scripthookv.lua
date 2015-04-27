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