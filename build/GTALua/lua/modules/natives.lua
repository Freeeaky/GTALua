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
				table.insert(return_values, c_type)
			else
				table.insert(native_args, arg)
			end
		end
	end
	
	-- push arguments
	for i = 1, #native_args, 1 do
		-- TODO: Add support for more types
		print("push number")
		c:PushNumber(native_args[i])
	end
	
	-- call
	print("calling...")
	if c:Call() then
		print("time to get results")
		for i = 1, #return_values, 1 do
			if return_values[i] == "number" then
				return_values[i] = c:GetResultNumber(i - 1)
			end
		end
		
		print("got results, back")
		return unpack(return_values)
	end
	
	-- error, native not found
	error("CNativeReg:Call - Unknown Native Hash!")
end