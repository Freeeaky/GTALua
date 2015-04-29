-- Game
game = {}

-- IsPaused
function game.IsPaused()
	return natives.UI.IS_PAUSE_MENU_ACTIVE()
end

-- CreatePed
function game.CreatePed(model_hash, vec)
	local ped_handle = natives.PED.CREATE_PED(26, model_hash, vec.x, vec.y, vec.z, 0, true, true)
	return Ped(ped_handle)
end