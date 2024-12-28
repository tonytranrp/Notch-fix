#include "ViewModel.h"

ViewModel::ViewModel() : Module("ViewModel", "Changes hand model", Category::RENDER, 0x0) {
	addEnumSetting("MainHand", "NULL", { "Right", "Left" }, &mainHand);
	addBoolCheck("Translate Hand", "NULL", &translate);
	addBoolCheck("Scale Hand", "NULL", &scale);
	addBoolCheck("Rotate Hand", "NULL", &rotate);
	addSlider<float>("TransX", "NULL", &translateVec.x, -2.f, 2.f);
	addSlider<float>("TransY", "NULL", &translateVec.y, -2.f, 2.f);
	addSlider<float>("TransZ", "NULL", &translateVec.z, -5.f, 2.f);
	addSlider<float>("ScaleX", "NULL", &scaleVec.x, -3.f, 3.f);
	addSlider<float>("ScaleY", "NULL", &scaleVec.y, -2.f, 2.f);
	addSlider<float>("ScaleZ", "NULL", &scaleVec.z, -2.f, 5.f);
	addSlider<float>("RotX", "NULL", &rotateVec.x, 0.f, 2.f);
	addSlider<float>("RotY", "NULL", &rotateVec.y, 0.f, 2.f);
	addSlider<float>("RotZ", "NULL", &rotateVec.z, 0.f, 2.f);
	addSlider<float>("Angle", "Hand rotation angle", &rotAngle, -6.3f, 6.3f);
	addBoolCheck("Reset", "Resets all the values to default", &reset);
}

void ViewModel::onTick(LocalPlayer* actor) {
	if (reset) {
		translateVec = Vec3(0, 0, 0);
		scaleVec = Vec3(1.f, 1.f, 1.f);
		rotateVec = Vec3(0.1f, 0.f, 0.f);
		rotAngle = 0.f;
		reset = false;
	}
}