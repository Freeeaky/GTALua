--
-- Check out our the Wiki!
--     http://wiki.gtalua.com/index.php/Main_Page
--     http://wiki.gtalua.com/index.php/Getting_Started
--     http://wiki.gtalua.com/index.php/API
--
-- I recommend matching addon name & script thread name
example_timers = ScriptThread("example_04_timers")

-- Run
function example_timers:Run()
	-- There are 2 different ways of setting up timers
	--
	-- 1: timer.Simple
	-- A simple timer callback is executed once
	-- It cannot be cancelled
	timer.Simple(1000, function(text, text_2)
		print("timer.Simple timer callback here")
		print("Text: ", text)
		print("Text #2: ", text_2)
	end, "This is a parameter for the callback function!", "As many as you like.")
	
	-- 2: timer.Create
	-- This timer has more options thn the Simple Timer
	--
	-- Parameters:
	--   1: Name (make sure its unique)
	--   2: Interval / Time (also in milliseconds)
	--   3: Repetitions (use -1 for unlimited repetitions)
	--   4: Callback
	timer.Create("example_04_timers_sample_timer", 1500, 2, function(text)
		print("timer.Create timer callback here!")
		print("our text: ", text)
	end, "This function can also take parameters!")
	
	--
	-- Callbacks
	--
	-- In the above examples the functions were passed as parameter
	-- You can also use functions that are in your thread
	timer.Simple(5000, "FunctionCallback")
end

-- Function Callback
function example_timers:FunctionCallback()
	print("FunctionCallback here!")
end

-- Register
example_timers:Register()