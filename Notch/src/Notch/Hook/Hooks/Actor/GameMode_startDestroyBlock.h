#pragma once
#include <Windows.h>
#include <iostream>
#include "../BaseHook.h"
#include "../../../Utils/Memory.h"
#include "../../../Client/Module/ModuleManager.h"
#include "../../../GameData.h"
class GameMode__startDestroyBlockHook : public Hook {
public:
	static inline void* oGameModestartDestroyBlock;
	static bool oGameModestartDestroyBlockHookCallBack(GameMode* _this, Vec3i const& pos, uint8_t face, bool& isDestroyedOut) {
		if (!moduleMgr->isInitialized())
			return Memory::CallFunc<bool, GameMode*, Vec3i const&, uint8_t, bool&>(oGameModestartDestroyBlock, _this, pos, face, isDestroyedOut);
		PacketMine* pmMod = moduleMgr->getModule<PacketMine>();
		if (pmMod->isEnabled()) {
			pmMod->setBreakPos(pos, face);
			return false;
		}
		return Memory::CallFunc<bool, GameMode*, Vec3i const&, uint8_t, bool&>(oGameModestartDestroyBlock, _this, pos, face, isDestroyedOut);
	};
	virtual void Initialize() override {
		std::thread initThread([this]() {
			while (Game.getLocalPlayer() == nullptr) Sleep(100);
			auto gmvfTable = *(uintptr_t**)(Game.getLocalPlayer()->getGameMode());
			Memory::CreateHook((void*)gmvfTable[1], &oGameModestartDestroyBlockHookCallBack, &oGameModestartDestroyBlock, "GameMode::startDestroyBlock Hook");
		});
		initThread.detach();
	};
};