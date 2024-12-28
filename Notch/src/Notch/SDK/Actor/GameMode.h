#pragma once

#include "../../Utils/HMath.h"

#include "Actor.h"

#include <functional>

class InputMode;
class ItemStack;
class Block;
class Actor;

class GameMode {
    uintptr_t** VTable;
public:
    BUILD_ACCESS(this, class Player*, plr, 0x8);
    BUILD_ACCESS(this, Vec3i, breakPos, 0x10);
    BUILD_ACCESS(this, float, lastBreakProgress, 0x20);
    BUILD_ACCESS(this, float, breakProgress, 0x24);
public:
    virtual ~GameMode();// 0 Destructor
    virtual __int64 startDestroyBlock(Vec3i const& pos, unsigned char blockSide, bool& isDestroyedOut); // 1
    virtual __int64 destroyBlock(const Vec3i&, unsigned char blockSide); // 2
    virtual __int64 continueDestroyBlock(Vec3i const& a1, unsigned char a2, Vec3 const& a3, bool& a4); // 3
    virtual __int64 stopDestroyBlock(Vec3i const&); // 4
    virtual __int64 startBuildBlock(Vec3i const& a1, unsigned char a2, bool auth); // 5
    virtual __int64 buildBlock(Vec3i const& a1, unsigned char a2, bool auth); // 6
    virtual __int64 continueBuildBlock(Vec3i const& a1, unsigned char a2); // 7
    virtual __int64 stopBuildBlock(); // 8
    virtual __int64 tick(); // 9
    virtual __int64 getPickRange(InputMode const& a1, bool a2); // 10
    virtual __int64 useItem(class ItemStack& a1); // 11
    virtual __int64 useItemOn(ItemStack& a1, Vec3i const& a2, unsigned char a3, Vec3 const& a4, class Block const* a5); // 12
    virtual __int64 interact(Actor* a1, Vec3 const& a2); // 13
    virtual __int64 attack(Actor&); // 14
    virtual __int64 releaseUsingItem(); // 15
    virtual void setTrialMode(bool a1); // 16
    virtual void isInTrialMode(); // 17
    virtual __int64 registerUpsellScreenCallback(std::function<void> a3); // 18
public:
    float getDestroyRate(Block const& block) {
        using getDestroyRate = float(__fastcall*)(GameMode*, Block const&);
        static getDestroyRate getDestroyRateFunc = reinterpret_cast<getDestroyRate>(getSig("GameMode::getDestroyRate"));
        return getDestroyRateFunc(this, block);
    }

    void baseUseItem(ItemStack& a1) {
        using GM_baseUseItem_t = void (*)(GameMode*, ItemStack&);
        static GM_baseUseItem_t baseUseItem = reinterpret_cast<GM_baseUseItem_t>(getSig("GameMode::baseUseItem"));  //"ItemUseInventoryTransaction::handle - destroy block failed, rending blocks around area to player"

        return baseUseItem(this, a1);
    }
};