-- Includes
include("modules/event.lua")

-- Test
console.Log("TEST")

thread = ScriptThread()

thread:OnRun(function()
	console.Log("ScriptThread: RUN")
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
	print("event callback")
	engine.RegisterScriptThread(thread)
end)