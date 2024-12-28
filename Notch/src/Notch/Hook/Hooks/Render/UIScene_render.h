#pragma once

#include "../BaseHook.h"

#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/Manager.h"

#include "../../../SDK/Render/MinecraftUIRenderContext.h"
#include "../../../SDK/Render/ScreenView.h"

class UIScene__renderHook : public Hook {
public:
	static inline void* UIScene__render;
	static void UIScene__renderCallback(void* _this, ScreenContext* screenContext, const void* renderObj) {
		//return;

		return Memory::CallFunc<void, void*, ScreenContext*, const void*>(UIScene__render, _this, screenContext, renderObj);
	};
	virtual void Initialize() override {
		Memory::CreateHook(getSig("UIScene::render"), &UIScene__renderCallback, &UIScene__render, "UIScene::render Hook");
	}
};