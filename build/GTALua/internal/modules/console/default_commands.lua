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

-- reload_addon
function console.cmd_reload_addon(name)
	-- Syntax
	if name == nil then
		print("Syntax: reload_addon [name]")
		return
	end
	
	-- Load
	addon.Load(name)
end
console.RegisterCommand("reload_addon", console.cmd_reload_addon)