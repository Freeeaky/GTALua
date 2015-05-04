-- streaming
streaming = {}

-- Model Loading
function streaming.RequestModel(hash)
	natives.STREAMING.REQUEST_MODEL(hash)
end
function streaming.HasModelLoaded(hash)
	return natives.STREAMING.HAS_MODEL_LOADED(hash)
end
function streaming.ReleaseModel(hash)
	natives.STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(hash)
end

-- Anim Dict Loading
function streaming.RequestAnimDict(name)
	natives.STREAMING.REQUEST_ANIM_DICT(name)
end
function streaming.HasAnimDictLoaded(name)
	return natives.STREAMING.HAS_ANIM_DICT_LOADED(name)
end
function streaming.ReleaseAnimDict(name)
	natives.STREAMING.REMOVE_ANIM_DICT(name)
end

-- Loading & Waiting
function streaming.RequestAndWaitForModel(thread, hash)
	if streaming.HasModelLoaded(hash) then return end
	streaming.RequestModel(hash)
	
	while thread:IsRunning() do
		if streaming.HasModelLoaded(hash) then return end
		thread:Wait(1)
	end
end
function streaming.RequestAndWaitForAnimDict(thread, name)
	if streaming.HasAnimDictLoaded(name) then return end
	streaming.RequestAnimDict(name)
	
	while thread:IsRunning() do
		if streaming.HasAnimDictLoaded(name) then return end
		thread:Wait(1)
	end
end