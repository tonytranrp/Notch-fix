#pragma once

#include "../Module.h"
#include "../../ModuleManager.h"

class ArrayList : public Module {
public:
	bool showKey = true;
	bool showMode = true;

	bool bottom = true;
	bool outline = true;
	float alpha = 0.35;
	float blurStrength = 5.f;
	int mode = 0;
	ArrayList();
	~ArrayList();

	virtual void onImGuiRender(ImDrawList* d) override;
};
