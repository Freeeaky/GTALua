-- Addons
addon = {}
addon.AddonTable = {}

-- Load Addon
function addon.Load(name)
	-- TODO: Add error handling, version checking, etc.
	-- TODO: Config files
	include("../../addons/"..name.."/main.lua")
end