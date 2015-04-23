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
	print("ok....")
	engine.RegisterScriptThread(thread)
end)