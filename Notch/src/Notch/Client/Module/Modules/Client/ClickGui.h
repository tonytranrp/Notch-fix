#pragma once
#include "Debugconsole.h"
#include "../Module.h"
#include "../../ModuleManager.h"
#include "../../../Config/ConfigManager.h"
#include "../../../../Libraries/Libs/ImFX/imfx.h"
#include "../../../../Utils/ImGuiUtils.h"
#include "../../../../GameData.h"
#include "../../../../Utils/Input.h"

void getModuleListByCategory(Category category, std::vector<Module*>& modList);

struct ClickWindow {
	std::string windowName;
	Vec2 pos;
	float scrolloffset = 0.f;
	float yOffset;
	bool extended = true;
	bool isDragging = false;
	Category category;
	std::vector<Module*> modList;

	ClickWindow(const Vec2& Pos, const Category& c) {
		this->pos = Pos;
		this->extended = true;
		if (c == Category::COMBAT) this->windowName = "Combat";
		else if (c == Category::MISC) this->windowName = "Misc";
		else if (c == Category::RENDER) this->windowName = "Render";
		else if (c == Category::MOVEMENT) this->windowName = "Movement";
		else if (c == Category::PLAYER) this->windowName = "Player";
		else if (c == Category::CLIENT) this->windowName = "Client";
		else if (c == Category::UNKNOW) this->windowName = "Unknow";

		getModuleListByCategory(c, modList);
	}
};

class ClickGui : public Module {
private:
	std::vector<ClickWindow*> windowList;
	bool isLeftClickDown = false;
	bool isRightClickDown = false;
	bool isHoldingLeftClick = false;
	bool isHoldingRightClick = false;
	Vec2 startDragPos = Vec2(0.f, 0.f);
	float openDuration = 0.f;
	bool initClickGui = false;
	void init();
	bool guiMove = false;
	bool tooltips = true;
	bool isShiftDown = false;
	bool isBackKeyDown = false;
	std::string searchingModule;
	int lastKeyPress = -1;
	bool* isChoosingKeyBindPtr = nullptr;
	bool isSearching = false;
public:
	float blurStrength = 7.5f;
	ClickGui();
	~ClickGui();

	virtual void onMouseClickUpdate(int mouseButton, bool isDown, bool& cancel) override;
	virtual void onKey(int key, bool isDown, bool& cancel) override;
	virtual void render(ImDrawList* drawlist);
	virtual bool isVisible() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};