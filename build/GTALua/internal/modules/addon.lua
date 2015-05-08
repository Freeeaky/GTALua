-- Addons
addon = {}
addon.AddonTable = {}

-- Load Addon
function addon.Load(name)
	-- TODO: Add version checking, etc.
	-- TODO: Config files
	include("../../addons/"..name.."/main.lua")
	
	-- Game Pause
	if IsScriptEngineInitialized() and game.IsPaused() then
		print("[addon.Load] Game is paused. Script Thread will reset after you unpaused it!")
	end
end

-- Unload Addon
function addon.Unload(name)
	local thread = scripthookv.FindThread(name)
	if thread ~= nil then
		thread:Kill()
	else
		print("[addon.Unload] Can't find addon ", name)
	end
end