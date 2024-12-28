#pragma once

#include "../../../Client/Module/ModuleManager.h"

class MouseDevice__feedHook : public Hook {
public:
	static inline void* oMouseDevice_feed;
	static void oMouseDevice_feedCallBack(__int64 a1, char mouseButton, char isDown, __int16 mouseX, __int16 mouseY, __int16 relativeMovementX, __int16 relativeMovementY, char a8) {
		bool cancel = false;
		Game.mousepos = Vec2(mouseX, mouseY);
		// MouseButtons
		// 0 = mouse move
		// 1 = left click
		// 2 = right click
		// 3 = middle click
		// 4 = scroll   (isDown: 120 (SCROLL UP) and -120 (SCROLL DOWN))

		moduleMgr->onMouseClickUpdate(mouseButton, (bool)isDown, cancel);
		if (mouseButton == 4) moduleMgr->onWheelScroll(isDown > 0);

		if (!cancel)
			return Memory::CallFunc<void, __int64, char, char, __int16, __int16, __int16, __int16, char>(
				oMouseDevice_feed, a1, mouseButton, isDown, mouseX, mouseY, relativeMovementX, relativeMovementY, a8
			);
	}

	virtual void Initialize() override {
		Memory::CreateHook(getSig("MouseDevice::feed"), (void*)&oMouseDevice_feedCallBack, &oMouseDevice_feed, "MouseDevice::feed Hook");
	}
};  