#pragma once

#include "../../Utils/Memory.h"
#include "../../Utils/HMath.h"
#include "../Actor/Actor.h"
enum struct HitType : int {
	BLOCK = 0,
	ENTITY = 1,
	AIR = 3
};

class HitResult {
public:
	BUILD_ACCESS(this, Vec3, start, 0x008);
	BUILD_ACCESS(this, Vec3, end, 0x0014);
	BUILD_ACCESS(this, HitType, hitType, 0x0020);
	BUILD_ACCESS(this, int8_t, BlockFace, 0x0024);
	BUILD_ACCESS(this, Vec3i, hitBlock, 0x0028);
	BUILD_ACCESS(this, Vec3, hitPos, 0x034);
	BUILD_ACCESS(this, Actor*, entity, 0x038);
	BUILD_ACCESS(this, bool, isLiquid, 0x004C);
	BUILD_ACCESS(this, int32_t, liquidFace, 0x0050);
	BUILD_ACCESS(this, Vec3i, liquidBlockPos, 0x0054);
	BUILD_ACCESS(this, Vec3, liquidPos, 0x0060);
	BUILD_ACCESS(this, bool, indirectHit, 0x006C);
};