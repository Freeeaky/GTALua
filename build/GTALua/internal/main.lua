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

-- Helper
include("game/game.lua")
include("game/streaming.lua")

-- Main
function _main()
	-- Nothing to do here (anymore)
	
	-- Success
	return true
end