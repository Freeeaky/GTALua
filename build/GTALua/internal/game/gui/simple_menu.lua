-- Simple Menu
class 'GUISimpleMenu'

-- CTor
function GUISimpleMenu:__init()
	self.ActiveIndex = 1
	self.Options = {}
	self.Closed = false
end

-- Closed
function GUISimpleMenu:IsClosed()
	return self.Closed
end
function GUISimpleMenu:IsOpen() return not self.Closed end
function GUISimpleMenu:SetClosed(b)
	self.Closed = b or false
end
function GUISimpleMenu:Close() self:SetClosed(true) end
function GUISimpleMenu:Open() self:SetClosed(false) end

-- Update
function GUISimpleMenu:Update()
	-- Closed-Check
	if self.Closed then
		return
	end
	
	--
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
	for k,v in pairs(self.Options) do		
		if k == self.ActiveIndex then
			gui.DrawRect(x, y, self.Width, self.OptionHeight, option_color_selected)
		else
			gui.DrawRect(x, y, self.Width, self.OptionHeight, option_color)
		end
		
		gui.DrawText(x + 0.002, y, v.Text)
		y = y + self.OptionHeight
	end
	
	-- Controls
	self:UpdateControls()
end

-- Controls
function GUISimpleMenu:UpdateControls()	
	-- back
	if (IsKeyDown(KEY_DELETE) or IsKeyDown(KEY_BACK)) and self.CanBeClosed then
		self.Closed = true
		gui.BeepBack()
	end
	
	-- down
	if IsKeyDown(KEY_NUMPAD2) then
		self.ActiveIndex = self.ActiveIndex + 1
		gui.BeepNavUpDown()
	end
	
	-- up
	if IsKeyDown(KEY_NUMPAD8) then
		self.ActiveIndex = self.ActiveIndex - 1
		gui.BeepNavUpDown()
	end
	
	-- confirm
	if IsKeyDown(KEY_NUMPAD5) then
		local opt = self.Options[self.ActiveIndex]
		opt.Callback()
		gui.BeepSelect()
	end
	
	-- out of range check
	local options_count = #self.Options
	if self.ActiveIndex > options_count then
		self.ActiveIndex = 1
	end
	if self.ActiveIndex < 1 then
		self.ActiveIndex = options_count
	end
end

-- Add Option
function GUISimpleMenu:AddOption(name, callback_name_or_func, ...)
	local args = {...}
	local callback = callback_name_or_func
	if type(callback) == "string" then
		callback = function()
			return self.Thread[callback_name_or_func](self.Thread, self, unpack(args))
		end
	elseif type(callback) == "function" then
		callback = function()
			callback_name_or_func(self, unpack(args))
		end
	end
	
	table.insert(self.Options, {
		Text = name,
		Callback = callback
	})
end

-- CTor
function gui.SimpleMenu(thread, settings)
	local data = GUISimpleMenu()
	
	-- Settings
	data.Thread = thread
	data.Title = settings.Title or "Simple Menu"
	data.x = settings.x or 0
	data.y = settings.y or 0
	data.Width = settings.Width or 0.2
	data.OptionHeight = settings.OptionHeight or 0.03
	data.TitleHeight = settings.TitleHeight or 0.05
	data.CanBeClosed = settings.CanBeClosed or true
	
	return data
end