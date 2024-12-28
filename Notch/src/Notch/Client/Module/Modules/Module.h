#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "../../../Libraries/Libraries.h"
#include "../../../Utils/HMath.h"
#include "../../../Utils/ColorUtil.h"
#include <glm/glm/ext/matrix_clip_space.hpp>
#include <glm/glm/ext/matrix_relational.hpp>
#include <glm/glm/ext/matrix_transform.hpp>
#include <glm/glm/gtc/constants.hpp>
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/trigonometric.hpp>
using json = nlohmann::json;

enum class Category {
	COMBAT = 0,
	MISC = 1,
	RENDER = 2,
	MOVEMENT = 3,
	PLAYER = 4,
	CLIENT = 5,
	UNKNOW = 6
};

enum class SettingType {
	BOOL,
	SLIDER,
	ENUM,
	COLOR,
	KEYBIND,
	TEXT,
};

enum class ValueType {
	FLOAT_T,
	INT_T,
	COLOR_T,
};

struct SettingValue {
	union {
		float _float;
		int _int;
		bool _bool;
		std::string _text;
	};
};

class Setting {
public:
	std::string settingName;
	std::string description;
	SettingType settingType;
	ValueType valueType;
	SettingValue* valuePtr = nullptr;
	SettingValue* minValue = nullptr;
	SettingValue* maxValue = nullptr;
	UIColor* colorPtr = nullptr;
	int* enumValue = nullptr;
	bool extended = false;
	std::vector<std::string> enumList;
	bool isChoosingKeybind = false;
	bool isInputingKeybind = false;
	bool isDragging = false;
	bool isDragging2 = false;
	bool isDragging3 = false;
	Vec2 pos;
	bool visible = true;
	float hueDuration = 0.f;
	~Setting();
};
class Actor;
class LocalPlayer;
class MinecraftUIRenderContext;
class Module {
private:
	std::string moduleName;
	std::string modName = "NULL";
	std::string description;
	Category category;
	bool enabled = false;
	bool visible = true;
	int toggleMod = 0;
	int keybind = 0x0;
	std::vector<Setting*> settingList;
public:
	// ClickGui stuff
	bool extended = false;
	// ArrayList
	float ArrayListDuration = 0.f;
public:
	inline const Category& getCategory() { return this->category; }
	inline const int getKeybind() { return this->keybind; }
	inline void setKeybind(int key) { this->keybind = key; };
	inline std::vector<Setting*>* getSettings() { return &this->settingList; }
	Module(const std::string& mName, const std::string& des, Category c = Category::UNKNOW, int k = 0x0);
protected:
	//Module(const std::string& mName, const std::string& des, Category c = Category::UNKNOW, int k = 0x0);
	template<typename T>
	void addSlider(const std::string& sliderName, const std::string& des, T* valuePtr, T min, T max) {
		Setting* setting = new Setting();
		setting->settingName = sliderName;
		setting->description = des;
		setting->settingType = SettingType::SLIDER;
		if constexpr (std::is_same_v<T, float>)
			setting->valueType = ValueType::FLOAT_T;
		if constexpr (std::is_same_v<T, int>)
			setting->valueType = ValueType::INT_T;
		setting->valuePtr = (SettingValue*)(valuePtr);
		setting->minValue = (SettingValue*)(new T(min));
		setting->maxValue = (SettingValue*)(new T(max));
		this->settingList.push_back(setting);
	}
	Setting* addBoolCheck(const std::string& name, const std::string& des, bool* boolPtr) {
		Setting* setting = new Setting();
		setting->settingName = name;
		setting->description = des;
		setting->settingType = SettingType::BOOL;
		setting->valuePtr = (SettingValue*)(boolPtr);
		this->settingList.push_back(setting);

		return setting;
	}
	Setting* addEnumSetting(const std::string& name, const std::string& des, const std::vector<std::string>& enumList, int* defaultValue) {
		Setting* setting = new Setting();
		setting->settingName = name;
		setting->description = des;
		setting->settingType = SettingType::ENUM;
		setting->enumList = enumList;
		setting->enumValue = defaultValue;
		this->settingList.push_back(setting);

		return setting;
	}
	Setting* addColorPicker(const std::string& name, const std::string& des, UIColor* colorPtr) {
		Setting* setting = new Setting();
		setting->settingName = name;
		setting->description = des;
		setting->settingType = SettingType::COLOR;
		setting->colorPtr = colorPtr;
		static const Vec2 colorPickerSize = Vec2(136.f, 100.f);
		static float h, s, v;
		ImGui::ColorConvertRGBtoHSV((float)colorPtr->r / 255.f, (float)colorPtr->g / 255.f, (float)colorPtr->b / 255.f, h, s, v);
		setting->hueDuration = h;
		setting->pos = Vec2(s * colorPickerSize.x, (v - 1.f) * -1.f * colorPickerSize.y);
		this->settingList.push_back(setting);

		return setting;
	}
	Setting* addKeybindSetting(const std::string& name, const std::string& des, int* keyPtr) {
		Setting* setting = new Setting();
		setting->settingName = name;
		setting->description = des;
		setting->settingType = SettingType::KEYBIND;
		setting->valuePtr = (SettingValue*)(keyPtr);
		this->settingList.push_back(setting);

		return setting;
	}
	Setting* addTextInputSetting(const std::string& name, const std::string& des, std::string* textPtr) {
		Setting* setting = new Setting();
		setting->settingName = name;
		setting->description = des;
		setting->settingType = SettingType::TEXT;
		setting->valuePtr = (SettingValue*)(textPtr);
		this->settingList.push_back(setting);

		return setting;
	};

	virtual Setting* showSetting(std::string name) {
		for (auto& setting : settingList) {
			if (strcmp(setting->settingName.c_str(), name.c_str()) == 0) {
				setting->visible = true;
				return setting;
			}
		}
	};
	virtual Setting* hideSetting(std::string name) {
		for (auto& setting : settingList) {
			if (strcmp(setting->settingName.c_str(), name.c_str()) == 0) {
				setting->visible = false;
				return setting;
			}
		}
	};
public:
	~Module();
	static std::string obfuscate(const std::string& input) {
		std::string result = input;
		const char key = 0x7F;  // You can choose a different key

		for (char& c : result) {
			c ^= key;
		}

		return result;
	}

	static std::string deobfuscate(const std::string& input) {
		return obfuscate(input);  // XOR encryption is symmetric
	}
	virtual std::string getModuleName();
	virtual std::string getModName();
	virtual std::string getDescription();
	virtual bool isEnabled();
	virtual void setEnabled(bool enabled);
	virtual void toggle();
	virtual bool isVisible();
	virtual void onEnable();
	virtual void onTick(LocalPlayer* actor);
	virtual void onDisable();
	virtual void onSaveConfig(json* currentConfig);
	virtual void onLoadConfig(json* config);
	virtual void onMouseClickUpdate(int key, bool isDown, bool& cancel);
	virtual void onWheelScroll(bool direction);
	virtual void onKeyUpdate(int key, bool isDown);
	virtual void onKey(int key, bool isDown, bool& cancel);
	virtual void onImGuiRender(ImDrawList* drawlist);
	virtual void ClickGuiChanger() {};
	virtual void onLevelRender();
	virtual void onJoiningServer();
	virtual void onRender(MinecraftUIRenderContext* c);
};
