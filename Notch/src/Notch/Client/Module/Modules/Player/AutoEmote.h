#pragma once
#include "../Module.h"
#include "../../../../SDK/Actor/Actor.h"

class AutoEmote : public Module {
private:

	int EmoteDelay = 2;
public:
	AutoEmote();

	virtual void onTick(LocalPlayer* actor) override;
};