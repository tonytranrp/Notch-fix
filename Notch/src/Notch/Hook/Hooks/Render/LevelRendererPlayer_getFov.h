#pragma once

#include "../BaseHook.h"

#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/Manager.h"

class LevelRendererPlayer__getFovHook : public Hook {
public:
	static inline void* LevelRendererPlayergetFov;
	static float LevelRendererPlayergetFovCallback(void* _this, float a, bool applyEffects) {
		if (!moduleMgr->isInitialized())
			return Memory::CallFunc<float, void*, float, bool>(LevelRendererPlayergetFov, _this, a, applyEffects);;
		static Camera* cameraMod = moduleMgr->getModule<Camera>();
		 if (cameraMod->isEnabled() && cameraMod->morefov)
			return cameraMod->fov;
		return Memory::CallFunc<float, void*, float, bool>(LevelRendererPlayergetFov, _this, a, applyEffects);;
	};
	virtual void Initialize() override {
		Memory::CreateHook(getSig("LevelRendererPlayer::getFov"), &LevelRendererPlayergetFovCallback, &LevelRendererPlayergetFov, "LevelRendererPlayer::getFov Hook");
	}
};