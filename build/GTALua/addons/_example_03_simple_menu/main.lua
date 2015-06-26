--
-- Check out our the Wiki!
--     http://wiki.gtalua.com/index.php/Main_Page
--     http://wiki.gtalua.com/index.php/Getting_Started
--     http://wiki.gtalua.com/index.php/API
--
-- I recommend matching addon name & script thread name
example_simple_menu = ScriptThread("example_simple_menu") 

-- Callback
function example_simple_menu:MenuCallback_Test(menu, text)
	print("Given message: ", text)
	menu:Close()
end

-- Run
function example_simple_menu:Run()
	-- Setup Menu
	local menu = gui.SimpleMenu(self, {
		Title = "Menu 123", -- title of the menu
		x = 0.03, -- x-coordinate, 0.0 = left, 1.0 = right
		y = 0.02, -- y-coordinate, 0.0 = top, 1.0 = bottom
		Width = 0.23, -- width of the whole menu
		TitleHeight = 0.06, -- height of the title box
		TitleFont = 1, -- title font family
		TitleFontScale = 0.5, -- title font scale
		TitleColor = Color(0,0,0), -- background color of the title
		TitleTextColor = Color(255,255,255), -- text color for the title
		OptionHeight = 0.04, -- height of an option
		OptionFont = 4, --  font family of an option
		OptionTextScale = 0.54, -- text scale (option text)
		OptionTextColor = Color(255,255,255), -- text color (if not selected)
		SelectedOptionTextColor = Color(180,255,180), -- text color if currently selected
		CanBeClosed = true -- allow close
	})
	
	-- Controls
	-- Note: The controls given here are all defaults
	-- You only need to bind changed keys
	menu:BindControl("option_up", KEY_NUMPAD8)
	menu:BindControl("option_down", KEY_NUMPAD2)
	menu:BindControl("confirm", KEY_NUMPAD5)
	menu:BindControl("back", KEY_BACK)
	
	-- Add Options
	menu:AddOption("A", "MenuCallback_Test", "he pressed a")
	menu:AddOption("B", "MenuCallback_Test", "he pressed b!")
	menu:AddOption("C", "MenuCallback_Test", "he pressed c!")
	
	-- Update
	while self:IsRunning() do
		-- Update
		menu:Update()
		
		-- Reopen?
		if menu:IsClosed() and IsKeyDown(KEY_F9) then
			menu:Open()
		end
		
		-- Note: If you have a menu in your script, change the wait-time to 0!
		self:Wait(0)
	end
end

-- Register
example_simple_menu:Register()
