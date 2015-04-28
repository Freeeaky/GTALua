-- Natives
-- Add Call Layout
function CNativeReg:AddCallLayout(layout)
	self.m_sCallLayout = layout
	self.m_bHasCallLayout = true
end

-- Has Call Layout
function CNativeReg:HasCallLayout()
	return self.m_bHasCallLayout
end

-- Call Native by Call Layout
function CNativeReg:__call(...)
	local function _err(msg)
		error("CNativeReg:Call ["..self.m_sCategory.."/"..self.m_sName.."] "..msg)
	end

	-- check call layout
	if not self.m_bHasCallLayout then
		_err("Native doesn't have a Call Layout!")
	end
	
	-- arguments
	local args = {...}
	local native_args = {}
	local arg_count = string.len(self.m_sCallLayout)
	
	-- return value
	local return_value = nil
	local is_void = false
	
	-- parse
	local parsing_return_values = false
	for i = 1, arg_count, 1 do
		local arg = args[i]
		
		-- find type
		local type_char = self.m_sCallLayout:sub(i, i)
		local c_type = scripthookv.TypeTable[type_char]
		if c_type == nil and type_char ~= ")" then
			_err("Unknown argument type "..type_char)
		end
		
		-- return value parsing
		if type_char == ")" then
			parsing_return_values = true
		else
			-- type check
			if not parsing_return_values and c_type ~= type(arg) then
				_err("Argument type mismatch (index "..i.." - got "..type(arg).." expected "..c_type..")")
			end
			
			-- process
			if parsing_return_values then
				if type_char == "v" then
					is_void = true
					break
				end
				return_value = type_char
			else
				table.insert(native_args, {arg, type_char})
			end
		end
	end
	
	-- init
	scripthookv.InitNative(self)

	-- push arguments
	for i = 1, #native_args, 1 do
		local value, type_char = native_args[i][1], native_args[i][2]
		local c_type = scripthookv.TypeTable[type_char]
		
		if type_char == "i" or type_char == "a" or type_char == "u"  then
			scripthookv.NativePushInt(value)
		elseif type_char == "f" then
			scripthookv.NativePushFloat(value)
		elseif c_type == "string" then
			print("push string ", value)
			scripthookv.NativePushString(value)
			print("pushed")
		elseif c_type == "Vector" then
			scripthookv.NativePushVector(value)
		elseif c_type == "boolean" then
			scripthookv.NativePushBool(value == true)
		end
	end
	
	-- call & return
	local c_type = scripthookv.TypeTable[return_value]
	
	if is_void then
		scripthookv.NativeCall_Void()
		return
	elseif return_value == "i" or return_value == "a" or return_value == "u" then
		print("call get i")
		return scripthookv.NativeCall_GetInt()
	elseif return_value == "f" then
		return scripthookv.NativeCall_GetFloat()
	elseif c_type == "string" then
		return scripthookv.NativeCall_GetString()
	elseif c_type == "Vector" then
		return scripthookv.NativeCall_GetVector()
	elseif c_type == "boolean" then
		return scripthookv.NativeCall_GetBool()
	end
	
	-- error, native not found
	_err("Unknown return value type!")
end