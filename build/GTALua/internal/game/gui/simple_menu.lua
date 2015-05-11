-- Simple Menu
class 'GUISimpleMenu'

-- CTor
function GUISimpleMenu:__init()
	self.ActiveIndex = 1
	self.Options = {}
	self.Closed = false
	self.Controls = {
		option_up = KEY_NUMPAD8,
		option_down = KEY_NUMPAD2,
		confirm = KEY_NUMPAD5,
		back = KEY_BACK
	}
end

-- Bind Control
function GUISimpleMenu:BindControl(name, key_code)
	if self.Controls[name] == nil then
		error("GUISimpleMenu: Unknown control \""..tostring(name).."\"")
	end
	if key_code == nil then
		error("Invalid keycode (nil)")
	end
	
	self.Controls[name] = key_code
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
	local option_color = Color(0,0,0,150)
	local option_color_selected = Color(0,0,0,190)
	
	-- Title
	gui.DrawRect(x, y, self.Width, self.TitleHeight, self.TitleColor)
	gui.DrawText(x + 0.003, y + 0.003, self.Title, {
		TextScale = 0.8,
		Color = self.TitleTextColor
	})
	y = y + self.TitleHeight	

	-- Objects
	for k,v in pairs(self.Options) do		
		local col = self.OptionTextColor
		if k == self.ActiveIndex then
			col = self.SelectedOptionTextColor
			gui.DrawRect(x, y, self.Width, self.OptionHeight, option_color_selected)
		else
			gui.DrawRect(x, y, self.Width, self.OptionHeight, option_color)
		end
	
		gui.DrawText(x + 0.002, y, v.Text, {
			TextScale = self.OptionTextScale,
			Color = col
		})
		y = y + self.OptionHeight
	end
	
	-- Controls
	self:UpdateControls()
end

-- Controls
function GUISimpleMenu:UpdateControls()	
	-- back
	if IsKeyDown(self.Controls["back"]) and self.CanBeClosed then
		self.Closed = true
		gui.BeepBack()
	end
	
	-- down
	if IsKeyDown(self.Controls["option_down"]) then
		self.ActiveIndex = self.ActiveIndex + 1
		gui.BeepNavUpDown()
	end
	
	-- up
	if IsKeyDown(self.Controls["option_up"]) then
		self.ActiveIndex = self.ActiveIndex - 1
		gui.BeepNavUpDown()
	end
	
	-- confirm
	if IsKeyDown(self.Controls["confirm"]) then
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
	
	-- Title
	data.Title = settings.Title or "Simple Menu"
	data.TitleColor = settings.TitleColor or Color(0,0,0) 
	data.TitleTextColor = settings.TitleTextColor or Color(255,255,255)
	data.TitleHeight = settings.TitleHeight or 0.03
	
	-- Options
	data.OptionTextScale = settings.OptionTextScale or 0.54
	data.OptionTextColor = settings.OptionTextColor or Color(255,255,255)
	data.SelectedOptionTextColor = settings.SelectedOptionTextColor or Color(200,255,200)
	
	-- Sizing
	data.x = settings.x or 0
	data.y = settings.y or 0
	data.Width = settings.Width or 0.2
	data.OptionHeight = settings.OptionHeight or 0.03
	
	-- Other
	data.Thread = thread
	data.CanBeClosed = settings.CanBeClosed or true
	
	return data
end