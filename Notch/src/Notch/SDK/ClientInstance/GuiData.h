#pragma once
#include "../../Manager/Manager.h"
#include "../../Utils/HMath.h"
#include "../../Utils/TextFormat.h"
class GuiData {
public:
    BUILD_ACCESS(this, Vec2, realSize, 0x0030);
    BUILD_ACCESS(this, Vec2, realSize2, 0x0038);
    BUILD_ACCESS(this, Vec2, scaledSize, 0x0040);
    BUILD_ACCESS(this, float, guiScale, 0x004C);
    BUILD_ACCESS(this, float, scaleMultiplier, 0x0050);
    BUILD_ACCESS(this, int16_t, MousePosX, 0x006A);
    BUILD_ACCESS(this, int16_t, MousePosY, 0x006C);
};