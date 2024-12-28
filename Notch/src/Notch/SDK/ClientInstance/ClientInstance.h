#pragma once
#include "../../Utils/Memory.h"
#include "../../Manager/Manager.h"
#include "../../version.h"

#include "GuiData.h"
#include "LoopbackPacketSender.h"
#include "LevelRenderer.h"
class ClientInstance {
public:
    uintptr_t** VTable;
    BUILD_ACCESS(this, class MinecraftGame*, minecraftGame, 0xC8);
    BUILD_ACCESS(this, class Minecraft*, minecraft, 0xD0);
    BUILD_ACCESS(this, LoopbackPacketSender*, loopbackPacketSender, 0xF0);
    BUILD_ACCESS(this, GuiData*, guiData, 0x558);
    BUILD_ACCESS(this, LevelRenderer*, LevelRender, 0xE0);
public:
    glmatrixf* getrefdef() {
        return (glmatrixf*)((uintptr_t)(this) + getOffset("ClientInstance::getrefdef"));
    }
    auto getBlockSource() -> class BlockSource* {
        return Memory::CallVFunc<BlockSource*>(this, 28);
    }

    auto getLocalPlayer() -> class LocalPlayer* {
        return Memory::CallVFunc<LocalPlayer*>(this, 29);
    };
    Vec3 getOrigin() {
        return LevelRender->getOrigin();
    };

    void grabMouse() {
        Memory::CallVFunc<void>((void*)this, getIndex("ClientInstance::grabMouse"));
    };
    void releaseMouse() {
        Memory::CallVFunc<void>((void*)this, getIndex("ClientInstance::releaseMouse"));
    };
    Vec2 getMousePos();
    Vec2 getFov() {
        return Vec2(
            (float)((uintptr_t)(this) + getOffset("ClientInstance::getFovX")), // X
            (float)((uintptr_t)(this) + getOffset("ClientInstance::getFovY"))  // Y
        );
    }
};
