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

-- Convert World to Screen coordinates
function game.WorldToScreen(p)
	local m_screenX = CMemoryBlock(4)
	local m_screenY = CMemoryBlock(4)
	local screenX = nil
	local screenY = nil
	local result = nil
	if natives.GRAPHICS._WORLD3D_TO_SCREEN2D(p.x, p.y, p.z, m_screenX, m_screenY) then
		screenX = m_screenX:ReadFloat(0)
		screenY = m_screenY:ReadFloat(0)
		result = {x=screenX, y=screenY}
	else
		result = nil
	end
	return result
end

-- Get coordinate in front of cam
function game.GetCoordsInFrontOfCam(distance)
	distance = distance or 5000
	local GameplayCamCoord = natives.CAM.GET_GAMEPLAY_CAM_COORD()
	local GameplayCamRot = natives.CAM.GET_GAMEPLAY_CAM_ROT(2)

	local tanX = natives.SYSTEM.COS(GameplayCamRot.x) * distance
	local xPlane = natives.SYSTEM.SIN(GameplayCamRot.z * -1.0) * tanX + GameplayCamCoord.x
	local yPlane = natives.SYSTEM.COS(GameplayCamRot.z * -1.0) * tanX + GameplayCamCoord.y
	local zPlane = natives.SYSTEM.SIN(GameplayCamRot.x) * distance + GameplayCamCoord.z

	return {x=xPlane, y=yPlane, z=zPlane}
end

-- Get the aimed entity and aimed point via RayCast
function game.GetRaycastTarget(distance, flags, entity)
	local p1 = natives.CAM.GET_GAMEPLAY_CAM_COORD()
	local p2 = game.GetCoordsInFrontOfCam(distance)
	local ray = natives.WORLDPROBE._CAST_RAY_POINT_TO_POINT(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, flags, entity, 7)
	local m_hit = CMemoryBlock(4)
	local m_endCoords = CMemoryBlock(24)
	local m_surfaceNormal = CMemoryBlock(24)
	local m_entityHit = CMemoryBlock(4)
	local enum = natives.WORLDPROBE._GET_RAYCAST_RESULT(ray, m_hit, m_endCoords, m_surfaceNormal, m_entityHit)
	local hit = m_hit:ReadDWORD32(0) == 1
	local endCoords = nil
	local surfaceNormal = nil
	local entityHit = nil
	local ent = nil
	if hit then
		endCoords = {x=m_endCoords:ReadFloat(0), y=m_endCoords:ReadFloat(2), z=m_endCoords:ReadFloat(4)}
		entityHit = m_entityHit:ReadDWORD32(0)
		ent = Entity(entityHit)
		if ent:IsPed() then
			ent = Ped(entityHit)
		end
		if ent:IsVehicle() then
			ent = Vehicle(entityHit)
		end
		if ent:IsObject() then
			ent = Object(entityHit)
		end
	end
	m_hit:Release()
	m_endCoords:Release()
	m_surfaceNormal:Release()
	m_entityHit:Release()
	return ent, endCoords
end

-- Get the Ped or Vehicle driver as target (Uses Raycast)
function game.GetTargetPed(distance, flags, entity)
	local ent = select(1, game.GetRaycastTarget(distance, flags, entity))
	if ent then
		if ent:IsVehicle() then
			ent = ent:GetPedInSeat(VehicleSeatDriver)
		else
			if not ent:IsPed() then
				ent = nil
			end
		end
	end
	return ent
end
