#pragma once
class CameraAvoidanceSystemUtil__calculateHardDistanceConstraintHook : public Hook {
public:
	static inline void* detour;
	static void CameraDetour(__int64 _this, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6) {
		if (!moduleMgr->isInitialized()) return Memory::CallFunc<void, __int64, __int64, __int64, __int64, __int64>(detour, _this, a2, a3, a4, a5, a6);
		Camera* cameraMod = moduleMgr->getModule<Camera>();
		if (!cameraMod->isEnabled() && cameraMod->viewclip)
			Memory::CallFunc<void, __int64, __int64, __int64, __int64, __int64>(detour, _this, a2, a3, a4, a5, a6);
	}
	virtual void Initialize() override {
		Memory::CreateHook(getSig("CameraAvoidanceSystemUtil::calculateHardDistanceConstraint"), (void*)&CameraDetour, &detour, "CameraAvoidanceSystemUtil::calculateHardDistanceConstraint Hook");
	}
};
