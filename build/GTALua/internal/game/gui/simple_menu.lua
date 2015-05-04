-- Simple Menu
GUISimpleMenu = {}

-- Draw
function GUISimpleMenu:Draw()
	local x, y = self.x, self.y
	local title_color = Color(0,0,0)
	local option_color = Color(0,0,0,150)
	local option_color_selected = Color(0,0,0,190)
	
	-- Title
	gui.DrawRect(x, y, self.Width, self.TitleHeight, title_color)
	gui.DrawText(x + 0.003, y + 0.003, self.Title, {
		TextScale = 0.8
	})
	y = y + self.TitleHeight	

	-- Objects
	local index = 0
	for k,v in pairs(self.Options) do
		index = index + 1
		
		if index == self.ActiveIndex then
			gui.DrawRect(x, y, self.Width, self.OptionHeight, option_color_selected)
		else
			gui.DrawRect(x, y, self.Width, self.OptionHeight, option_color)
		end
		
		gui.DrawText(x + 0.002, y, v)
		y = y + self.OptionHeight
	end
	self.OptionsCount = index
	
	-- Controls
	self:UpdateControls()
end

-- Controls
function GUISimpleMenu:UpdateControls()	
	-- back
	if IsKeyDown(KEY_DELETE) or IsKeyDown(KEY_BACK) then
		self.Result = false
		gui.BeepBack()
	end
	
	-- down
	if IsKeyDown(KEY_NUMPAD2) then
		self.ActiveIndex = self.ActiveIndex + 1
		gui.Beep()
	end
	
	-- up
	if IsKeyDown(KEY_NUMPAD8) then
		self.ActiveIndex = self.ActiveIndex - 1
		gui.Beep()
	end
	
	-- confirm
	if IsKeyDown(KEY_NUMPAD5) then
		self.Result = self.ActiveIndex
		gui.BeepSelect()
	end
	
	-- out of range check
	if self.ActiveIndex > self.OptionsCount then
		self.ActiveIndex = 1
	end
	if self.ActiveIndex < 1 then
		self.ActiveIndex = self.OptionsCount
	end
end

-- Result
function GUISimpleMenu:GetResult()
	local r = self.Result
	if r ~= nil then
		local index = 0
		for k,v in pairs(self.Options) do
			index = index + 1
			if index == self.ActiveIndex then
				r = k
			end
		end
	end
	self.Result = nil
	return r
end

-- Wait for Result
function GUISimpleMenu:WaitForResult(thread, max_wait_time)
	max_wait_time = max_wait_time or -1
	local wait_until 
	if max_wait_time ~= -1 then
		wait_until = game.GetTime() + max_wait_time
	end
	
	while thread:IsRunning() and (max_wait_time == -1 or game.GetTime() < wait_until) do
		local res = self:GetResult()
		if res ~= nil then
			return res
		end
		self:Draw()
		thread:Wait(0)
	end
end

-- CTor
function gui.Menu(settings, options)
	local data = GUISimpleMenu
	
	-- Settings
	data.Title = settings.Title or "Simple Menu"
	data.x = settings.x or 0
	data.y = settings.y or 0
	data.Width = settings.Width or 0.2
	data.OptionHeight = settings.OptionHeight or 0.03
	data.TitleHeight = settings.TitleHeight or 0.05 

	-- Data
	data.ActiveIndex = 1
	data.Options = options
	
	return data
end