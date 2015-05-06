-- Console
console = {}
console.Commands = {}

-- Register
function console.RegisterCommand(name, callback)
	console.Commands[name] = callback
end

-- Event Listener
event.AddListener("OnConsoleInput", "internal_consoleModule", function(command, args)
	local callback = console.Commands[command]
	if callback ~= nil then
		callback(unpack(args))
		return true
	end
end)

-- Default Commands
include("default_commands.lua")