-- Natives
function CNativeReg:Call(...)
	-- check call layout
	if not self.m_bHasCallLayout then
		error("CNativeReg:Call - Native doesn't have a Call Layout!")
		return
	end
	
	-- arguments
	local args = {...}
	local arg_count = string.len(self.m_sCallLayout)
	
	-- count
	if #args ~= arg_count then
		error("CNativeReg:Call - Argument count mismatch")
		return
	end
	
	-- native invoke struct
	local c = CInvokeNative(self)
	
	-- arguments
	for i = 1, arg_count, 1 do
		local arg = args[i]
		local c_type = self.m_sCallLayout:sub(i, i)
		local a_type = type(arg)
		
		if c_type == "i" and a_type == "number" then
			c:PushNumber(arg)
		else
			error("CNativeReg:Call - Argument type mismatch (argument "..i.." - got "..a_type.." expected "..c_type..")")
		end
	end
	
	-- call
	if c:Call() then return true end
	
	-- error, native not found
	error("CNativeReg:Call - Unknown Native Hash!")
end