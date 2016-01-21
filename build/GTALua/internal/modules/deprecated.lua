-- Deprecrated
_deprecated_ConsoleCommands = {}

function _deprecated_message(deprecated, version, replacement)
  print("[GTALua] " .. deprecated .. " is deprecated since version " .. version)

  if replacement then
    print("[GTALua] Use " .. replacement .. " instead.")
  else
    print("[GTALua] No alternative available.")
  end
  print("")
end

function _deprecated_function(deprecated, version, replacement)
  _deprecated_message(deprecated, version, replacement)
end

function _deprecated_command(command)
  table.insert(_deprecated_ConsoleCommands, command)
end


-- Since 1.1.2

-- Console : load_addon/reload_addon
function console.cmd_load_addon_deprecated(name)
  _deprecated_message("load_addon/reload_addon [name]", "1.1.2", "load/reload [addon name]")
  return console.cmd_load_addon(name)
end
console.RegisterCommand("load_addon", console.cmd_load_addon_deprecated)
console.RegisterCommand("reload_addon", console.cmd_load_addon_deprecated)
_deprecated_command("load_addon")
_deprecated_command("reload_addon")

-- Console : unload_addon
function console.cmd_unload_addon_deprecated(name)
  _deprecated_message("unload_addon [name]", "1.1.2", "unload [addon name]")
  return console.cmd_unload_addon(name)
end
console.RegisterCommand("unload_addon", console.cmd_unload_addon_deprecated)
_deprecated_command("unload_addon")
