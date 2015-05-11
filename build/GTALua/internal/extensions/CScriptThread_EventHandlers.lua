-- Setup
function CScriptThread:internal_EventHandlers_Setup()
	self.EventHandlers = {}
	self.EventQueue = {}
end

-- Add Handler
function CScriptThread:AddEventHandler(event_name, callback_name)
	-- Listener Name
	local listener_name = "CST_" .. self:GetName() .. "_" .. event_name .. "_" .. #self.EventHandlers
	
	-- Register Handler
	table.insert(self.EventHandlers, {
		EventName = event_name,
		ListenerName = listener_name,
		CallbackName = callback_name
	})

	-- Add Handler
	event.AddListener(event_name, listener_name, function(...)
		self:internal_EventHandlers_HandleEvent(event_name, listener_name, {...})
	end)
end

-- Event Handler
function CScriptThread:internal_EventHandlers_HandleEvent(event_name, listener_name, args)
	table.insert(self.EventQueue, {
		event_name,
		listener_name,
		args
	})
end

-- Call Event Handler
function CScriptThread:internal_EventHandlers_CallHandler(event_name, listener_name, args)
	-- Find Callback
	local data
	for _,v in pairs(self.EventHandlers) do
		if v.ListenerName == listener_name then
			data = v
			break
		end
	end
	
	-- Error
	if data == nil then
		error("ScriptThread: No data for "..event_name.." ("..listener_name..")")
	end
	
	-- Callback-Check
	local callback = self[data.CallbackName]
	if not callback or type(callback) ~= "function" then
		error("ScriptThread: Invalid callout "..data.CallbackName.." for event "..data.EventName.."!")
	end
	
	-- Callback
	callback(self, unpack(args))
end

-- Tick
function CScriptThread:internal_EventHandlers_OnTick()
	for _,event_handler_data in pairs(self.EventQueue) do
		local success, err = pcall(function()
			return self:internal_EventHandlers_CallHandler(unpack(event_handler_data))
		end)
		
		-- error handling
		if not success then
			print("[Lua] ScriptThread "..self:GetName().." Event Handler Error: "..err)
		end
	end
	
	-- clear queue
	self.EventQueue = {}
end

-- Destroy
function CScriptThread:internal_EventHandlers_Destroy()
	if self.EventHandlers == nil then return end
	
	-- Remove Event Handlers
	for _,v in pairs(self.EventHandlers) do
		event.RemoveListener(v.EventName, v.ListenerName)
	end
end