#pragma once

#include "../BaseHook.h"

#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/Manager.h"

class Options__getGammaHook : public Hook {
public:
	static inline void* OptionsgetGamma;
	static float OptionsgetGammaCallback(void* _this) {
		if (!moduleMgr->isInitialized())
			return Memory::CallFunc<float, void*>(OptionsgetGamma, _this);;
		static Camera* cameraMod = moduleMgr->getModule<Camera>();
		if (cameraMod->isEnabled() && cameraMod->fullbright)
			return cameraMod->intensity;
		return Memory::CallFunc<float, void*>(OptionsgetGamma, _this);;
	};
	virtual void Initialize() override {
		Memory::CreateHook(getSig("Options::getGamma"), &OptionsgetGammaCallback, &OptionsgetGamma, "Options::getGamma Hook");
	}
};