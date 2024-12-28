#pragma once

#include <iostream>
#include <optional>
#include "../Actor/Actor.h"
class Level {
public:
	std::vector<Actor*> getRuntimeActorList() {
		std::vector<Actor*> listOut;
		Memory::CallVFunc<void, decltype(&listOut)>(this, getIndex("Level::getRuntimeActorList"), &listOut);
		return listOut;
	};

	class HitResult& getHitResult() {
		return *hat::member_at<std::shared_ptr<HitResult>>(this, getOffset("Level::hitResult"));
	};
};
