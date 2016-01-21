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
