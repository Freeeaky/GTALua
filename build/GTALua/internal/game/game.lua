-- Game
game = {}

-- IsPaused
function game.IsPaused()
	return natives.UI.IS_PAUSE_MENU_ACTIVE()
end

-- Create Ped
function game.CreatePed(model_hash, vec)
	if not streaming.HasModelLoaded(model_hash) then
		error("You need to load the model before creating a Ped! Call streaming.RequestModel prior to calling game.CreatePed!")
	end

	local ped_handle = natives.PED.CREATE_PED(26, model_hash, vec.x, vec.y, vec.z, 0, true, true)
	return Ped(ped_handle)
end

-- Create Vehicle 
function game.CreateVehicle(model_hash, vec)
	if not streaming.HasModelLoaded(model_hash) then
		error("You need to load the model before creating a Vehicle! Call streaming.RequestModel prior to calling game.CreateVehicle!")
	end
	
	local veh_handle = natives.VEHICLE.CREATE_VEHICLE(model_hash, vec.x, vec.y, vec.z, 0, true, true)
	return Vehicle(veh_handle)
end

-- Time
function game.GetTime()
	--return natives.GAMEPLAY.GET_GAME_TIMER()
	return scripthookv.GetGameTime()
end