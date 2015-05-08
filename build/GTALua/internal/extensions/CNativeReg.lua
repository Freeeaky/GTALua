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

-- Exceptions
function type_exception_check(type_char, should_type, actual_type, value)
	-- number: 0/1 for bools
	if should_type == "number" and actual_type == "boolean" and (value == 1 or value == 0) then
		type_char = "b"
		should_type = "boolean"
	end
	
	-- unknown/any/int & CMemoryBlock
	if (type_char == "a" or type_char == "u" or type_char == "i") and actual_type == "CMemoryBlock" then
		type_char = "m"
		should_type = "CMemoryBlock"
	end
	
	-- no exception
	return type_char, should_type, value
end

-- Call Native by Call Layout
function CNativeReg:__call(...)
	local _err = "CNativeReg:Call ["..self.m_sCategory.."/"..self.m_sName.."]: "

	-- check call layout
	if not self.m_bHasCallLayout or self.m_sCallLayout == nil then
		error(_err .. "Native doesn't have a Call Layout!")
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
			error(_err .. "Unknown argument type "..type_char)
		end
		
		-- return value parsing
		if type_char == ")" then
			parsing_return_values = true
		else
			-- exception check
			type_char, c_type, arg = type_exception_check(type_char, c_type, type(arg), arg)
		
			-- type check
			if not parsing_return_values and c_type ~= type(arg) then
				error(_err .. "Argument type mismatch (index "..i.." - got "..type(arg).." expected "..c_type..")")
			end
			
			-- CMemoryBlock check
			if c_type == "CMemoryBlock" and not arg:IsValid() then
				error(_err .. "Argument index "..i.." is an invalid CMemoryBlock!")
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
			scripthookv.NativePushString(value)
		elseif c_type == "Vector" then
			scripthookv.NativePushVector(value)
		elseif c_type == "boolean" then
			scripthookv.NativePushBool(value == true)
		elseif c_type == "CMemoryBlock" then
			scripthookv.NativePushMemoryBlock(value)
		end
	end
	
	-- call & return
	local c_type = scripthookv.TypeTable[return_value]
	
	if is_void then
		scripthookv.NativeCall_Void()
		return
	elseif return_value == "i" or return_value == "a" or return_value == "u" then
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
	error(_err .. "Unknown return value type!")
end