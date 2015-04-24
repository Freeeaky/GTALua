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

-- Types
engine.TypeTable = {
	i = "number",
	f = "number",
	b = "boolean",
	v = "void",
	V = "Vector"
}

-- Call Native by Call Layout
function CNativeReg:Call(...)
	-- check call layout
	if not self.m_bHasCallLayout then
		error("CNativeReg:Call - Native doesn't have a Call Layout!")
	end
	
	-- arguments
	local args = {...}
	local native_args = {}
	local arg_count = string.len(self.m_sCallLayout)
	
	-- return value
	local return_values = {}
	local is_void = false
	if arg_count < 2 then
		-- no return values, void
		is_void = true
	end
	
	-- native invoke struct
	local c = CInvokeNative(self)
	
	-- parse
	local parsing_return_values = false
	for i = 1, arg_count, 1 do
		local arg = args[i]
		
		-- find type
		local type_char = self.m_sCallLayout:sub(i, i)
		local c_type = engine.TypeTable[type_char]
		if c_type == nil and type_char ~= ")" then
			error("CNativeReg:Call [Call Layout Parser]: Unknown argument type "..type_char)
		end
		
		-- return value parsing
		if type_char == ")" then
			parsing_return_values = true
		else
			-- type check
			if not parsing_return_values and c_type ~= type(arg) then
				error("CNativeReg:Call - Argument type mismatch (index "..i.." - got "..type(arg).." expected "..c_type..")")
			end
			
			-- process
			if parsing_return_values then
				if type_char == "v" then
					is_void = true
					break
				end
				table.insert(return_values, type_char)
			else
				table.insert(native_args, {arg, type_char})
			end
		end
	end

	-- push arguments
	for i = 1, #native_args, 1 do
		local value, type_char = native_args[i][1], native_args[i][2]
		local c_type = engine.TypeTable[type_char]
		
		if type_char == "i" then
			c:PushNumber(value)
		elseif type_char == "f" then
			c:PushFloat(value)
		elseif c_type == "Vector" then
			c:PushVector(value)
		elseif c_type == "boolean" then
			c:PushBool(value == true)
		end
	end
	
	-- call
	if c:Call() then
		if is_void then
			return
		end
		
		for i = 1, #return_values, 1 do
			local type_char = return_values[i]
			local c_type = engine.TypeTable[type_char]
			
			if type_char == "i" then
				return_values[i] = c:GetResultNumber(i - 1)
			elseif type_char == "f" then
				return_values[i] = c:GetResultFloat(i - 1)
			elseif c_type == "Vector" then
				return_values[i] = c:GetResultVector(i - 1)
			elseif c_type == "boolean" then
				return_values[i] = c:GetResultBool(i - 1)
			end
		end
		
		return unpack(return_values)
	end
	
	-- error, native not found
	error("CNativeReg:Call - Unknown Native Hash!")
end