#pragma once
#include "../Module.h"
class Camera : public Module {
public:
	bool viewclip = false;
	bool fullbright = false;
	bool morefov = false;
	int intensity = 12;
	float fov = 110.f;
	Camera();
	virtual void ClickGuiChanger() override;
};
