#pragma once
#include "../Module.h"
#include "../../../../SDK/Actor/Actor.h"
#include "../../../../SDK/Level/Level.h"
#include "../../../../GameData.h"

class KillAura : public Module {
public:
	KillAura();
	bool swing = false;
	float range = 8.f;
	int target = 1;
	std::vector<Actor*> entityList;
	void findEntity();
	virtual void onTick(LocalPlayer* plr);
	virtual void onImGuiRender(ImDrawList* d);
};