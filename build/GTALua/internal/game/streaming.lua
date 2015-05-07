-- streaming
streaming = {}

-- Model Loading
function streaming.RequestModel(hash)
	if streaming.HasModelLoaded(hash) then return end
	natives.STREAMING.REQUEST_MODEL(hash)
	
	-- Wait
	while not streaming.HasModelLoaded(hash) do
		coroutine.yield()
	end
end
function streaming.HasModelLoaded(hash)
	return natives.STREAMING.HAS_MODEL_LOADED(hash)
end
function streaming.ReleaseModel(hash)
	natives.STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(hash)
end

-- Anim Dict Loading
function streaming.RequestAnimDict(name)
	if streaming.HasAnimDictLoaded(name) then return end
	natives.STREAMING.REQUEST_ANIM_DICT(name)
	
	-- Wait
	while not streaming.HasAnimDictLoaded(name) do
		coroutine.yield()
	end
end
function streaming.HasAnimDictLoaded(name)
	return natives.STREAMING.HAS_ANIM_DICT_LOADED(name)
end
function streaming.ReleaseAnimDict(name)
	natives.STREAMING.REMOVE_ANIM_DICT(name)
end