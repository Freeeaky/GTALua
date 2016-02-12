-- help
function console.cmd_help()
	print("List of available commands:")
	print("----------------------------------------")
	for k,v in pairs(console.Commands) do
		if not utils.IsInArray(_deprecated_ConsoleCommands, k) then
			print(k)
		end
	end
	print("----------------------------------------")
end
console.RegisterCommand("help", console.cmd_help)

-- Load Addon
function console.cmd_load_addon(name)
	-- Syntax
	if name == nil then
		print("[GTALua] Syntax: load/reload [addon name]")
		return
	end

	-- Load
	print("[GTALua] Loading ", name, "...")
	addon.Load(name)
	print("")
end
console.RegisterCommand("reload", console.cmd_load_addon)
console.RegisterCommand("load", console.cmd_load_addon)

-- Unload Addon
function console.cmd_unload_addon(name)
	-- Syntax
	if name == nil then
		print("[GTALua] Syntax: unload [addon name]")
		return
	end

	-- Unload
	print("[GTALua] Unloading ", name, "...")
	addon.Unload(name)
	print("")
end
console.RegisterCommand("unload", console.cmd_unload_addon)

-- Reload All Addons
function console.cmd_reload_all_addons()
	print("[GTALua] Reloading all addons...")
	for  _,thread in pairs(scripthookv.ThreadList) do
		local name = thread:GetName()
		if name ~= "main_thread" then addon.Load(name) end
	end
	print("")
end
console.RegisterCommand("reloadall", console.cmd_reload_all_addons)

-- Show the running threads
function console.cmd_show_all_addons()
	print("[GTALua] List of all loaded addons...")
	for  _,thread in pairs(scripthookv.ThreadList) do
		local name = thread:GetName()
		print(name," Active:",thread:IsActive()," Running:",thread:IsRunning())
	end
	print("")
end
console.RegisterCommand("showall", console.cmd_show_all_addons)

-- Execute a Lua command
function console.cmd_lua(...)
	local cmd=table.concat(arg," ")
	local f=loadstring(cmd)
	if type(f) == "function" then
		local r=f()
		if r ~= nil then
			print(r)
		end
	else
		error("Input didn't evaluate to a function.")
	end
end
console.RegisterCommand("lua", console.cmd_lua)
