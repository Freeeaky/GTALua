-- help
function console.cmd_help()
	print("List of available commands:")
	print("----------------------------------------")
	for k,v in pairs(console.Commands) do
		print(k)
	end
	print("----------------------------------------")
end
console.RegisterCommand("help", console.cmd_help)

-- Load Addon
function console.cmd_load_addon(name)
	-- Syntax
	if name == nil then
		print("Syntax: load/reload [addon name]")
		return
	end

	-- Load
	print("Loading ", name, "...")
	addon.Load(name)
	print("")
end
console.RegisterCommand("reload", console.cmd_load_addon)
console.RegisterCommand("load", console.cmd_load_addon)

-- Unload Addon
function console.cmd_unload_addon(name)
	-- Syntax
	if name == nil then
		print("Syntax: unload [addon name]")
		return
	end

	-- Unload
	print("Unloading ", name, "...")
	addon.Unload(name)
	print("")
end
console.RegisterCommand("unload", console.cmd_unload_addon)

-- Reload All Addons
function console.cmd_reload_all_addons()
	print("Reloading all addons...")
	for  _,thread in pairs(scripthookv.ThreadList) do
		local name = thread:GetName()
		if name ~= "main_thread" then addon.Load(name) end
	end
	print("")
end
console.RegisterCommand("reloadall", console.cmd_reload_all_addons)
