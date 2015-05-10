-- ui
ui = {}

-- Create Blip
function ui.CreateBlip(x,y,z)
	if type(x) == "Vector" then
		y = x.y
		z = x.z
		x = x.x
	end
	
	-- Create
	return Blip(natives.UI.ADD_BLIP_FOR_COORD(x,y,z))
end

-- Get Active Blips
function ui.GetActiveBlipsCount()
	return natives.UI.GET_NUMBER_OF_ACTIVE_BLIPS()
end