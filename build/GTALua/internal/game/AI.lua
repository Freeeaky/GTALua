-- AI
AI = {}

-- Sequence
function AI.OpenSequenceTask()
	local c_handle = CMemoryBlock(4)
	natives.AI.OPEN_SEQUENCE_TASK(c_handle)
	local handle = c_handle:ReadDWORD32(0)
	c_handle:Release()
	return handle
end
function AI.CloseSequenceTask(handle)
	natives.AI.CLOSE_SEQUENCE_TASK(handle)
end
function AI.ClearSequenceTask(handle)
	local c_handle = CMemoryBlock(4)
	c_handle:WriteDWORD32(0, handle)
	natives.AI.CLEAR_SEQUENCE_TASK(c_handle)
	c_handle:Release()
end

-- Clear Tasks
function AI.ClearTasks(id)
	natives.AI.CLEAR_PED_TASKS(id)
end

--
-- Task Wrapper
--
-- Play Animation
-- id, anim_dict, anim_name required!
function AI.TaskPlayAnim(id, anim_dict, anim_name, speed, f_unknown, loop, last_anim, playback_rate, xlock, ylock, zlock)
	if not streaming.HasAnimDictLoaded(anim_dict) then
		error("AI.TaskPlayAnim: Animation Dict "..anim_dict.." not loaded!")
	end
	
	speed = speed or 8
	f_unknown = f_unknown or -8
	loop = loop or 0
	last_anim = last_anim or 0
	playback_rate = playback_rate or 0
	xlock = xlock or false
	ylock = ylock or false
	zlock = zlock or false
	natives.AI.TASK_PLAY_ANIM(id, anim_dict, anim_name, speed, f_unknown, loop, last_anim, playback_rate, xlock, ylock, zlock)
end

-- Perform Sequence
function AI.TaskPerformSequence(id, sequence_handle)
	natives.AI.TASK_PERFORM_SEQUENCE(id, sequence_handle)
end
