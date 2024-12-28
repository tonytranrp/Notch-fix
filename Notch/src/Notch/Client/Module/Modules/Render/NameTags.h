#pragma once
#include "../Module.h"
#include "../../ModuleManager.h"
#include "../../../../Libraries/Libs/ImFX/imfx.h"
#include "../../../../Utils/ImGuiUtils.h"
#include "../../../../Manager/Manager.h"
#include "../../../../GameData.h"

class NameTags : public Module {
public:
	std::vector<Actor*> entityList;
	bool ThirdPersonNameTag = true;
	static constexpr size_t instructionSize = 6;
	static inline char originalBytes[instructionSize] = {};
	static inline void* instructionPointer = nullptr;

	NameTags();
	virtual void onImGuiRender(ImDrawList*) override;
	virtual void onTick(LocalPlayer* actor) override;
	virtual void onDisable() override;
};