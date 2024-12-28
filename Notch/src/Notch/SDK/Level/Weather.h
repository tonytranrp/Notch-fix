#pragma once
#include "../../Utils/Memory.h"
#include <cstdint>

class Weather {
public:
	BUILD_ACCESS(this, int32_t, tick, 0x0030);

    BUILD_ACCESS(this, float, rainTransitionOld, 0x0034);
    BUILD_ACCESS(this, float, rainTransition, 0x0038);
    BUILD_ACCESS(this, float, rain, 0x003C);
    BUILD_ACCESS(this, float, thunderTransitionOld, 0x0040);
    BUILD_ACCESS(this, float, thunderTransition, 0x0044);
    BUILD_ACCESS(this, float, thunder, 0x0048);
    BUILD_ACCESS(this, float, skyDarkness, 0x004C);
private:
	virtual void Function0();
};