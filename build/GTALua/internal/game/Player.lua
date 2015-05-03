-- Player
class 'Player'(Ped)

-- Player CTor
function Player:__init(playerid)
	self.PlayerID = playerid
	Ped.__init(self, natives.PLAYER.GET_PLAYER_PED(playerid))
	
	self._type = "Player"
end

-- Local Player
function LocalPlayer()
	return Player(natives.PLAYER.GET_PLAYER_INDEX())
end

-- Name
function Player:GetName()
	return natives.PLAYER.GET_PLAYER_NAME(self.PlayerID)
end

-- Wanted Level
function Player:GetWantedLevel()
	return natives.PLAYER.GET_PLAYER_WANTED_LEVEL(self.PlayerID)
end
function Player:SetWantedLevel(i)
	natives.PLAYER.SET_PLAYER_WANTED_LEVEL(self.PlayerID, false)
	natives.PLAYER.SET_PLAYER_WANTED_LEVEL_NOW(self.PlayerID, false)
end
function Player:ClearWantedLevel()
	natives.PLAYER.CLEAR_PLAYER_WANTED_LEVEL(self.PlayerID)
end

-- Dead
-- Overwrites Entity.IsDead
function Player:IsDead()
	return natives.PLAYER.IS_PLAYER_DEAD(self.PlayerID)
end

-- Model
function Player:SetModel(h)
	if not streaming.HasModelLoaded(h) then
		error("You need to load the model before applying it to a Player!")
	end
	
	natives.PLAYER.SET_PLAYER_MODEL(self.PlayerID, h)
end