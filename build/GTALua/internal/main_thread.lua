-- Addons that dont have its own ASI will be running on the main thread
main_thread = ScriptThread("main_thread")

-- Add Thread
function main_thread:AddThread(thread)
	-- self-Check
	if thread:GetName() == self:GetName() then return end

	-- already registered?
	for _,v in pairs(self.ThreadList) do
		if v:GetName() == thread:GetName() then
			return
		end
	end
	
	-- register
	print("[GTALua] Addon "..thread:GetName().." will run on the main thread")
	table.insert(self.ThreadList, thread)
end

-- Kill Thread
function main_thread:KillThread(thread)
	-- self-Check, you never know
	if thread:GetName() == self:GetName() then return end
	
	-- find & remove
	for k,v in pairs(self.ThreadList) do
		if v:GetName() == thread:GetName() then
			print("[LuaScriptThread] Thread "..thread:GetName().." killed")
			table.remove(self.ThreadList, k)
			return
		end
	end
end

-- Register
main_thread:Register()