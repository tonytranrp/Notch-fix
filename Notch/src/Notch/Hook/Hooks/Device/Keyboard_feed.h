#pragma once
#include "../../../GameData.h"
#include "../../../Client/Module/ModuleManager.h"
class Keyboard__feedHook : public Hook {
public:
	static inline void* oKeyboard_feed;

	static void oKeyboard_feedCallBack(int key, bool isDown) {
		if ((GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState('L') & 0x8000) || key == VK_END) Game.uninject();
		bool cancel = false;
		moduleMgr->onKeyUpdate(key, isDown, cancel);
		if (!cancel)
			return Memory::CallFunc<void, int, bool>(
				oKeyboard_feed, key, isDown
			);
	}

	virtual void Initialize() override {
		Memory::CreateHook(getSig("Keyboard::feed"), &oKeyboard_feedCallBack, &oKeyboard_feed, xorstr_("Keyboard::feed Hook"));
	}
};