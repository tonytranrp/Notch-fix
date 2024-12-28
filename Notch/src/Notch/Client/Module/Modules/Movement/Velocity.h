#pragma once

#include "../Module.h"
#include "../../../../SDK/Packet/Packet.h"
#include "../../../../SDK/Actor/Actor.h"
#include "../../../../GameData.h"
class Velocity : public Module {
public:
	float xModifier = 0.f;
	float yModifier = 0.f;

	Velocity();
	~Velocity();
};