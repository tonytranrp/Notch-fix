#pragma once
#include "../Module.h"
#include "../../../../Utils/ColorUtil.h"
#include "../../../../Utils/TimeUtil.h"
#include "../../ModuleManager.h"

class Colors : public Module {
private:
	UIColor mainColor = UIColor(255,255,255, 255);
	UIColor secondaryColor = UIColor(32, 32, 32, 255);
	int modeValue = 0;
	float seconds = 3.f;
	float saturation = 1.f;
	float brightness = 1.f;
	int seperation = 100;
private:
	float openDuration = 0.f;
public:
	Colors();
	~Colors();

	int getSeperationValue() {
		return this->seperation;
	}

	UIColor getColor(int index = 0, int multiplier = 1) {
		if (modeValue == 1) return ColorUtils::getRainbowColor(seconds, saturation, brightness, index);
		if (modeValue == 2) return ColorUtils::getWaveColor(mainColor, secondaryColor, index) * multiplier;
		return this->mainColor;
	}

	UIColor getRainbowColor(int index = 0) {
		return ColorUtils::getRainbowColor(seconds, saturation, brightness, index);
	}

	UIColor getWaveColor(int index = 0) {
		return ColorUtils::getWaveColor(mainColor, secondaryColor, index);
	}

	virtual bool isEnabled() override;
	virtual void setEnabled(bool enabled) override;
	virtual bool isVisible() override;
};