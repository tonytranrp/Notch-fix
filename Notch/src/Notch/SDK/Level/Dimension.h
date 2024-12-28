#pragma once
#include "../../Utils/Memory.h"

class Dimension {
public:
	BUILD_ACCESS(this, std::string, dimensionName, 0x20); // reclass
	BUILD_ACCESS(this, class BlockSource*, region, 0xC0); // xref: Actor::getBlockSource something like that
	BUILD_ACCESS(this, class VillageManager*, villageManager, 0x588); // xref: getVillageManager
};