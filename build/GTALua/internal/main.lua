-- Module
include("modules/event.lua")
include("modules/addon.lua")
include("modules/scripthookv.lua")
include("modules/console/console.lua")

-- Extensions
include("extensions/keycodes.lua")
include("extensions/vehicles.lua")
include("extensions/CNativeReg.lua")
include("extensions/CScriptThread.lua")
include("extensions/Vector.lua")
include("extensions/CMemoryBlock.lua")

-- Wrapper
include("game/Object.lua")
include("game/Entity.lua")
include("game/Vehicle.lua")
include("game/Ped.lua")
include("game/Player.lua")
include("game/AI.lua")
include("game/Blip.lua")

-- Helper
include("game/game.lua")
include("game/gui.lua")
include("game/streaming.lua")

-- Main Thread
include("main_thread.lua")

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
	print("")
	for _,addon_name in pairs(dir_list) do
		-- Do not load addons that start with "_"
		if addon_name:sub(1,1) == "_" then
			print("Ignored addon ", addon_name)
		else
			if scripthookv.FindThread(addon_name) then
				print("Addon "..addon_name.." is using an ASI loader")
			else
				print("Loading addon ", addon_name, "...")
				addon.Load(addon_name)
			end
		end
	end
	print("")
	
	-- Success
	return true
end