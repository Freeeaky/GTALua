--
-- Check out our the Wiki!
--     http://freeschi.com/w/index.php/Main_Page
--     http://freeschi.com/w/index.php/Getting_Started
--     http://freeschi.com/w/index.php/API
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
		TitleHeight = 0.05, -- height of the title box
		OptionHeight = 0.03, -- height of an option
		CanBeClosed = true -- allow close
	})
	
	-- Add Options
	menu:AddOption("A", "MenuCallback_Test", "he pressed a")
	menu:AddOption("B", "MenuCallback_Test", "he pressed b!")
	
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