-- Includes
include("modules/event.lua")
include("modules/natives.lua")

-- Test
thread = ScriptThread()

thread:OnRun(function()
	console.Log("ScriptThread: RUN")
	
	-- set time to 8:00:00
	natives.time.SetClockTime:Call(8,0,0)
	
	-- player ped id
	local localplayer = natives.player.GetPlayerPed:Call(-1)
	print("local player ped id: ", localplayer)
	
	if localplayer > 100 then
		local vec = natives.entity.GetEntityCoords:Call(localplayer)
		print("pos: ", vec.x, " ", vec.y, " ", vec.z)
	end
end)

thread:OnReset(function()
	console.Log("ScriptThread: RESET")
end)

thread:OnTick(function()
	console.Log("ScriptThread: TICK")
end)

thread:OnKill(function()
	console.Log("ScriptThread: KILL")
end)

event.AddListener("OnScriptEngineInitialized", "test_thread", function()
	engine.RegisterScriptThread(thread)
end)

console.Log("Testing...")