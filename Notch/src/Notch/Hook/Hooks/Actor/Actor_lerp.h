#pragma once
#include <Windows.h>
#include <iostream>
class Actor__lerpHook : public Hook{
public:
	static inline void* oActorLerp;
	static void oActorLerpHookCallBack(Actor* _this, Vec3 motVec) {
		if (Game.getLocalPlayer() != _this || !moduleMgr->isInitialized())
			return Memory::CallFunc<void, Actor*, Vec3>(oActorLerp, _this, motVec);
		static auto noKnockbackmod = moduleMgr->getModule<Velocity>();
		if (noKnockbackmod->isEnabled())
			motVec = _this->getStateVector()->Velocity.lerp(motVec, noKnockbackmod->xModifier, noKnockbackmod->yModifier, noKnockbackmod->xModifier);
		return Memory::CallFunc<void, Actor*, Vec3>(oActorLerp, _this, motVec);
	};
	virtual void Initialize() override {
		Memory::CreateHook(getSig("Actor::lerpMotion"), &oActorLerpHookCallBack, &oActorLerp, "Actor::lerpMotion Hook");
	};
};