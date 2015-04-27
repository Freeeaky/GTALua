-- test_script
thread = ScriptThread("test_script")

function thread:Run()
	print("Lua: thread:Run()")
	
	while true do
		print("still alive")
		if IsKeyDown(0x78) then
			print("ok!")
			local localplayer = natives.PLAYER.GET_PLAYER_PED(-1)
			print("lplayer: ", localplayer)
			
			local vec = natives.ENTITY.GET_ENTITY_COORDS(localplayer, true)
			print("pos: ", vec.x, vec.y, vec.z)
			
			local r = natives.VEHICLE.CREATE_VEHICLE(0xC703DB5F, vec.x, vec.y, vec.z, 0.0, true, true)
			print("r: ", r)
		end
		scripthookv.ThreadSleep(50)
	end
end

event.AddListener("OnScriptEngineInitialized", "Addmy", function()
	scripthookv.CreateThread(thread)
end)