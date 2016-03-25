-- Game
game = {}

-- IsPaused
function game.IsPaused()
	return natives.UI.IS_PAUSE_MENU_ACTIVE()
end

-- Create Ped
function game.CreatePed(model_hash, vec, heading)
	if not streaming.HasModelLoaded(model_hash) then
		error("You need to load the model before creating a Ped! Call streaming.RequestModel prior to calling game.CreatePed!")
	end

	if heading == nil then
		heading = 0
	end
	local ped_handle = natives.PED.CREATE_PED(26, model_hash, vec.x, vec.y, vec.z, heading, true, true)
	return Ped(ped_handle)
end

-- Create Vehicle 
function game.CreateVehicle(model_hash, vec, heading)
	if not streaming.HasModelLoaded(model_hash) then
		error("You need to load the model before creating a Vehicle! Call streaming.RequestModel prior to calling game.CreateVehicle!")
	end
	
	if heading == nil then
		heading = 0
	end
	local veh_handle = natives.VEHICLE.CREATE_VEHICLE(model_hash, vec.x, vec.y, vec.z, heading, true, true)
	return Vehicle(veh_handle)
end

-- Time
function game.GetTime()
	--return natives.GAMEPLAY.GET_GAME_TIMER()
	return scripthookv.GetGameTime()
end

-- Time - hours
function game.GetHours()
	return natives.TIME.GET_CLOCK_HOURS()
end

-- Time - minutes
function game.GetMinutes()
	return natives.TIME.GET_CLOCK_MINUTES()
end

-- Time - seconds
function game.GetSeconds()
	return natives.TIME.GET_CLOCK_SECONDS()
end

-- Set game TimerA
function game.SetTimerA(n)
	natives.SYSTEM.SETTIMERA(n)
end

-- Set game TimerB
function game.SetTimerB(n)
	natives.SYSTEM.SETTIMERB(n)
end

-- Get game TimerA
function game.GetTimerA()
	return natives.SYSTEM.TIMERA()
end

-- Get game TimerB
function game.GetTimerB()
	return natives.SYSTEM.TIMERB()
end

-- Request weapon asset (pass weapon hash)
function game.RequestWeaponAsset(weaponAsset)
	if not natives.WEAPON.HAS_WEAPON_ASSET_LOADED(weaponAsset) then
		natives.WEAPON.REQUEST_WEAPON_ASSET(weaponAsset, 1, true)
		-- Wait
		while not natives.WEAPON.HAS_WEAPON_ASSET_LOADED(weaponAsset) do
			coroutine.yield()
		end
	end
end

-- Shoot a bullet between two coordinates
function game.ShootBulletBetweenCoords(org, tgt, weapon, damage, speed)
	weapon = weapon or WeaponPistol
	damage = damage or 200
	speed = speed or 200
	game.RequestWeaponAsset(weapon)
	natives.GAMEPLAY.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(org.x, org.y, org.z, tgt.x, tgt.y, tgt.z, damage, true, weapon, 0, true, false, speed)
end
