#include "ArrayList.h"
#include "../../../../Utils/ImGuiUtils.h"

float textSize = 1.f;
ArrayList::ArrayList() : Module("ArrayList", "Display your enabled modules on the HUD!", Category::CLIENT, 0x0) {
	addBoolCheck("Show Keybind", "display of keybindings for each module", &showKey);
	addBoolCheck("Bottom", "position of the ArrayList to the bottom of the screen", &bottom);
	addBoolCheck("Outline", "outline around each module in the ArrayList.", &outline);
	addBoolCheck("Modes", "display of mode names next to each module.", &showMode);
	addSlider<float>("alpha", "Adjust the transparency of the background.", &alpha, 0.f, 1.f);
	addSlider<float>("Blur Strength", "strength of the background blur effect.", &blurStrength, 0.f, 20.f);
	addSlider<float>("Scale", "Arraylist Size", &textSize, 0.1f, 2.f);
	addEnumSetting("ModeType", "Choose the color for Mode Text", { "White", "Gray", }, &mode);
}

ArrayList::~ArrayList() {
}

struct ModuleContainer {
	Module* backingModule;
	std::string moduleName;
	std::string modName;
	std::string keybind;
	bool enabled;
	bool visible;
	float textWidth;
	Vec2* pos;

	ModuleContainer(Module* mod) {
		static ArrayList* ArrayListMod = moduleMgr->getModule<ArrayList>();
		this->backingModule = mod;
		this->moduleName = std::string(mod->getModuleName());
		this->keybind = mod->getKeybind();
		if (!mod->getModName().empty() && ArrayListMod->showMode) {
			this->modName = std::string(mod->getModName());
			std::string fullModuleName = this->moduleName + std::string(" ") + this->modName;
			this->textWidth = ImGuiUtils::getTextWidth(fullModuleName.c_str(), textSize);
		}
		else {
			this->textWidth = ImGuiUtils::getTextWidth(this->moduleName.c_str(), textSize);
		}
		this->enabled = mod->isEnabled();
		this->visible = mod->isVisible();
		this->pos = new Vec2(0.f, 0.f);
	}

	bool operator<(const ModuleContainer& other) const {
		if (this->textWidth == other.textWidth)
			return moduleName < other.moduleName;
		return this->textWidth > other.textWidth;
	}
};
void ArrayList::onImGuiRender(ImDrawList* d) {
	if (Game.getLocalPlayer() == nullptr) return;
	if (!Game.canUseMoveKeys()) return;
	ImGuiIO& io = ImGui::GetIO();
	Vec2 windowSize = Game.getGuiData()->realSize;
	
	static std::set<ModuleContainer> modContainerList;
	// Fill modContainerList with Modules
	std::vector<Module*>* moduleList = moduleMgr->getModuleList();
	{
		for (Module* it : *moduleList) {
			modContainerList.emplace(ModuleContainer(it));
		}
	}
	//std::vector<std::string> modListss;
	//for (Module* mod : *moduleList)
	//	modListss.push_back(mod->getModuleName());
	//logF(StringUtil::combine("Mod List : ", StringUtil::join(modListss, ", ")), "INFO");
	static const float textPadding = textSize * textSize;
	float textHeight = ImGuiUtils::getTextHeight(textSize) - textPadding;
	static const float lineWidth = 1.f;
	static const UIColor grayColor = UIColor(175, 175, 175, 255);
	static const bool textShadow = true;
	static const int seperation = 25;

	static Colors* colorsMod = moduleMgr->getModule<Colors>();
	float yOffset = this->bottom ? (windowSize.y - textHeight) : 0.f;
	int i = 0;
	int index = 0;
	// Update ModulePos
	for (auto it = modContainerList.begin(); it != modContainerList.end(); ++it) {
		float textWidth = it->textWidth;
		float xOffsetOri = windowSize.x - textWidth - textPadding * 2.f;
		it->pos->x = smoothLerp((it->enabled && it->visible) ? windowSize.x - xOffsetOri : -2.f, it->pos->x, io.DeltaTime * 15.f);
		if (it->pos->x > windowSize.x - xOffsetOri) it->pos->x = windowSize.x - xOffsetOri;
	}

	if (blurStrength > 0.f) { // Blur
		ImFX::Begin(d);
		for (auto it = modContainerList.begin(); it != modContainerList.end(); ++it) {
			//mainColor = ColorUtil::getRainbowColor(3.f, 1.f, 1.f, (bottom ? -i : i) * (seperation * 2.f));
			float textWidth = it->textWidth;
			float xOffsetOri = windowSize.x - textWidth - textPadding * 2.f;
			float xOffset = windowSize.x - it->pos->x;

			float duration = ((windowSize.x - xOffset) / (windowSize.x - xOffsetOri));
			if (duration < 0.f) duration = 0.f;

			Vec4 rectPos(xOffsetOri - 2.f, yOffset + (textHeight - textPadding * 2.f) * (bottom ? (textSize - duration) : 0.f), windowSize.x, yOffset + (textHeight - textPadding * 2.f) * (bottom ? textSize : duration));
			if (i == 0 && bottom) rectPos.w += textPadding * 2.f;
			if (duration > 0.01f) {
				//ImGuiUtils::drawShadowRect(rectPos, mainColor, 50.f * duration, false);
				ImFX::AddBlur(blurStrength, ImVec4(rectPos.x, rectPos.y, rectPos.z, rectPos.w));
				i++;
				yOffset += (textHeight - textPadding * 2.f) * duration * (bottom ? -textSize : textSize);
			}
		}
		ImFX::End();
	}

	yOffset = this->bottom ? (windowSize.y - textHeight) : 0.f;
	index = 0;

	Vec4 lastRect(0.f, 0.f, 0.f, 0.f);
	for (auto it = modContainerList.begin(); it != modContainerList.end(); ++it) {
		index++;
		std::string moduleName = it->moduleName;
		std::string modName = it->modName;
		float textWidth = it->textWidth;
		float xOffsetOri = windowSize.x - textWidth - textPadding * 2.f;
		float xOffset = windowSize.x - it->pos->x;

		//it->pos->x = smoothLerp((it->enabled && it->visible) ? windowSize.x - xOffsetOri : -2.f, it->pos->x, io.DeltaTime * 15.f);
		float duration = ((windowSize.x - xOffset) / (windowSize.x - xOffsetOri));
		if (duration < 0.f) duration = 0.f;

		Vec2 textPos(xOffset, yOffset - textPadding);
		Vec4 rectPos(xOffsetOri - 2.f, yOffset + (textHeight - textPadding * 2.f) * (bottom ? (textSize - duration) : 0.f), windowSize.x, yOffset + (textHeight - textPadding * 2.f) * (bottom ? textSize : duration));
		if (i == 0 && bottom) rectPos.w += textPadding * 2.f;
		if (duration > 0.01f) {
			UIColor mainColor(
				moduleMgr->getModule<Colors>()->getColor(index)
			);
			if (alpha * 255 > 0) ImGuiUtils::fillRectangle(rectPos, UIColor(0, 0, 0, alpha * 255));
			if (outline) {
				if (lastRect.x != 0.f) {
					if (!bottom) ImGuiUtils::fillRectangle(Vec4(lastRect.x - lineWidth, rectPos.y, rectPos.x, rectPos.y + lineWidth), mainColor);
					else ImGuiUtils::fillRectangle(Vec4(lastRect.x - lineWidth, rectPos.w, rectPos.x, rectPos.w - lineWidth), mainColor);
				}
				ImGuiUtils::fillRectangle(Vec4(rectPos.x - lineWidth, rectPos.y, rectPos.x, rectPos.w), mainColor);
			}
			ImGuiUtils::drawText(textPos, moduleName.c_str(), UIColor(mainColor.r, mainColor.g, mainColor.b, (float)(255 * duration)), textSize, textShadow);
			if (!it->backingModule->getModName().empty() && showMode) {
				std::string spacing = moduleName + " ";
				float ModuleWidth = ImGuiUtils::getTextWidth(spacing.c_str(), textSize);
				if (mode == 0)
					ImGuiUtils::drawText(Vec2(textPos.x + ModuleWidth, textPos.y), modName.c_str(), UIColor(255, 255, 255, (float)(255 * duration)), textSize, textShadow);
				if (mode == 1)
					ImGuiUtils::drawText(Vec2(textPos.x + ModuleWidth, textPos.y), modName.c_str(), UIColor(181, 181, 181, (float)(255 * duration)), textSize, textShadow);
			}
			lastRect = rectPos;
			i++;
			yOffset += (textHeight - textPadding * 2.f) * duration * (bottom ? -textSize : textSize);
		}
	}
	UIColor mainColor = colorsMod->getColor();
	if (outline) {
		if (!bottom) ImGuiUtils::fillRectangle(Vec4(lastRect.x - lineWidth, lastRect.w, windowSize.x, lastRect.w + lineWidth), mainColor);
		else ImGuiUtils::fillRectangle(Vec4(lastRect.x - lineWidth, lastRect.y, windowSize.x, lastRect.y - lineWidth), mainColor);
	}
	modContainerList.clear();
}
