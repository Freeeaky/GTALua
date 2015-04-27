-- Module
include("modules/event.lua")
include("modules/addon.lua")
include("modules/scripthookv.lua")
include("modules/console/console.lua")

-- Extensions
include("extensions/CNativeReg.lua")
include("extensions/CScriptThread.lua")

-- Main
function _main()
	-- Find Addons
	local success, dir_list, _file_list = file.FindFiles("GTALua/addons/*")
	if not success then
		print("Failed to get directory list for GTALua/addons/")
		print("Unable to load addons!")
		return false
	end
	
	-- Load Addons
	for _,addon_name in pairs(dir_list) do
		print("Loading addon ", addon_name, "...")
		addon.Load(addon_name)
		print("")
	end
	
	-- Success
	return true
end