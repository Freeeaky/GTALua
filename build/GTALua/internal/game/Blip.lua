-- Blip
class 'Blip'

-- CTor
function Blip:__init(handle)
	self.ID = handle
end

-- type & string
function Blip:__tostring()
	return "[Blip]"
end
function Blip:__type()
	return "Blip"
end

-- Exists
function Blip:Exists()
	return natives.UI.DOES_BLIP_EXIST(self.ID)
end
function Blip:_CheckExists()
	if not self:Exists() then
		error("Blip is not valid!")
	end
end

-- Delete
function Blip:Delete()
	self:_CheckExists()
	local c_blip = CMemoryBlock(4)
	c_blip:WriteDWORD32(0, self.ID)
	natives.UI.REMOVE_BLIP(c_blip)
	c_blip:Release()
end

-- Position
function Blip:GetCoords()
	self:_CheckExists()
	return natives.UI.GET_BLIP_COORDS(self.ID)
end

-- Sprite
function Blip:SetSprite(i)
	self:_CheckExists()
	natives.UI.SET_BLIP_SPRITE(self.ID, i)
end

function Blip:GetSprite()
	self:_CheckExists()
	return natives.UI.GET_BLIP_SPRITE(self.ID)
end

-- Flashing/Pulse
function Blip:SetFlashing(b)
	self:_CheckExists()
	natives.UI.SET_BLIP_FLASHES(self.ID,b)
end

function Blip:SetFlashingAlternate(b)
	self:_CheckExists()
	natives.UI.SET_BLIP_FLASHES_ALTERNATE(self.ID, b)
end

function Blip:SetFlashTimer(n)
	self:_CheckExists()
	natives.UI.SET_BLIP_FLASH_TIMER(self.ID, n)
end

function Blip:SetFlashInterval(n)
	self:_CheckExists()
	natives.UI.SET_BLIP_FLASH_INTERVAL(self.ID, n)
end

function Blip:IsFlashing()
	self:_CheckExists()
	return natives.UI.IS_BLIP_FLASHING(self.ID)
end

function Blip:Pulse()
	self:_CheckExists()
	natives.UI.PULSE_BLIP(self.ID)
end

-- Route
function Blip:ShowRoute(b)
	self:_CheckExists()
	natives.UI.SET_BLIP_ROUTE(self.ID,b)
end

function Blip:SetRouteColour(colour)
	self:_CheckExists()
	natives.UI.SET_BLIP_ROUTE_COLOUR(self.ID, colour)
end

-- Visible
function Blip:SetVisible(b)
	self:_CheckExists()
	natives.UI.SET_BLIP_DISPLAY(self.ID, b)
end

function Blip:SetAlpha(n)
	self:_CheckExists()
	natives.UI.SET_BLIP_ALPHA(self.ID,n)
end

function Blip:GetAlpha()
	self:_CheckExists()
	return natives.UI.GET_BLIP_ALPHA(self.ID)
end

-- Iterators
function Blip:GetFirstInfoID()
	self:_CheckExists()
	return natives.UI.GET_FIRST_BLIP_INFO_ID(self.ID)
end

-- Color
function Blip:SetPrimaryColour(color)
	self:_CheckExists()
	natives.UI.SET_BLIP_COLOUR(self.ID, color)
end

function Blip:SetSecondaryColour(color)
	self:_CheckExists()
	natives.UI.SET_BLIP_SECONDARY_COLOUR(color)
end

function Blip:GetColour()
	self:_CheckExists()
	return natives.UI.GET_BLIP_COLOUR(self.ID)
end

function Blip:GetHUDColour()
	self:_CheckExists()
	return natives.UI.GET_BLIP_HUD_COLOUR(self.ID)
end

-- Info ID
function Blip:GetNextInfoID()
	self:_CheckExists()
	return natives.UI.GET_NEXT_BLIP_INFO_ID(self.ID)
end

function Blip:GetInfoIDCoord()
	self:_CheckExists()
	return natives.UI.GET_BLIP_INFO_ID_COORD(self.ID)
end

function Blip:GetInfoIDDisplay()
	self:_CheckExists()
	return natives.UI.GET_BLIP_INFO_ID_DISPLAY(self.ID)
end

function Blip:GetInfoIDType()
	self:_CheckExists()
	return natives.UI.GET_BLIP_INFO_ID_TYPE(self.ID)
end

function Blip:GetInfoIDEntityIndex()
	self:_CheckExists
	return natives.UI.GET_BLIP_INFO_ID_ENTITY_INDEX(self.ID)
end

function Blip:GetInfoIDPickupIndex()
	self:_CheckExists()
	return natives.UI.GET_BLIP_INFO_ID_PICKUP_INDEX(self.ID)
end

-- Others
function Blip:SetFade(n,n2)
	self:_CheckExists()
	natives.UI.SET_BLIP_FADE(self.ID,n or 0,n2 or 0)
end

function Blip:SetRotation(n)
	self:_CheckExists()
	natives.UI.SET_BLIP_ROTATION(self.ID, n)
end

function Blip:SetShortRange(b)
	self:_CheckExists()
	natives.UI.SET_BLIP_AS_SHORT_RANGE(self.ID, b)
end

function Blip:IsShortRange()
	self:_CheckExists()
	return natives.UI.IS_BLIP_SHORT_RANGE(self.ID)
end

function Blip:IsOnMinimap()
	self:_CheckExists()
	return natives.UI.IS_BLIP_ON_MINIMAP(self.ID)
end

function Blip:SetHighDetail(b)
	self:_CheckExists()
	return natives.UI.SET_BLIP_HIGH_DETAIL(self.ID, b)
end

function Blip:SetScale(n)
	self:_CheckExists()
	natives.UI.SET_BLIP_SCALE(self.ID,n)
end

function Blip:SetPriority(n)
	self:_CheckExists()
	natives.UI.SET_BLIP_PRIORITY(self.ID, n)
end

function Blip:SetFriendly(b)
	self:_CheckExists()
	natives.UI.SET_BLIP_AS_FRIENDLY(self.ID, b)
end

function Blip:ShowBlipNumber(b)
	self:_CheckExists()
	if b == true then
		natives.UI.SHOW_NUMBER_ON_BLIP(self.ID, true)
	else
		natives.UI.HIDE_NUMBER_ON_BLIP(self.ID)
	end
end