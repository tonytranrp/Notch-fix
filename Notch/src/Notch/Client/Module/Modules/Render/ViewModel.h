#pragma once
#include "../Module.h"
class ViewModel : public Module {
public:
	int mainHand = 0;
	bool reset = false;
	bool translate = false;
	bool scale = false;
	bool rotate = false;
public:
	Vec3 translateVec;
	Vec3 scaleVec = Vec3(1.f, 1.f, 1.f);
	Vec3 rotateVec;
	float rotAngle = 0.1f;
public:
	ViewModel();
	virtual void onTick(LocalPlayer* gm) override;
};
