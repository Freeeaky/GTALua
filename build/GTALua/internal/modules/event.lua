-- event module
-- You can add/remove event listener, add your own events (and call them)
-- Each event listener has it's own name so it can be identified
event = {}
event.Listener = {}

-- Add Listener
function event.AddListener(event_name, listener_name, callback)
	if event.Listener[event_name] == nil then
		event.Listener[event_name] = {}
	end
	
	event.Listener[event_name][listener_name] = callback
end

-- Call Event Listener
-- This function calls ALL event listeners UNTIL a value is returned != nil
function event.Call(event_name, ...)
	if event.Listener[event_name] == nil then return end
	
	for k,v in pairs(event.Listener[event_name]) do
		local rv = v(...)
		if rv ~= nil then
			return rv
		end
	end
end

-- Remove Listener
function event.RemoveListener(event_name, listener_name)
	if event.Listener[event_name] == nil then return end
	event.Listener[event_name][listener_name] = nil
end