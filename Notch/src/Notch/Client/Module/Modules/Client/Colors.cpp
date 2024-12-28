#include "Colors.h"

Colors::Colors() : Module("Colors", "Change the color of UI Elements.", Category::CLIENT) {
	addEnumSetting("Mode", "Change colors mode", { "Single", "Rainbow", "Wave" }, &modeValue);
	addSlider<float>("Seconds", "Changes rainbow speed.", &seconds, 1.f, 10.f);
	addSlider<float>("Saturation", "Changes rainbow saturation.", &saturation, 0.f, 1.f);
	addSlider<float>("Brightness", "Changes rainbow brightness.", &brightness, 0.f, 1.f);
	addSlider<int>("Seperation", "Changes color seperation.", &seperation, 0, 250);
	addColorPicker("Main Color", "Main Colors", &mainColor);
	addColorPicker("Second Color", "Secondary Colors", &secondaryColor);
}
Colors::~Colors() {
}
bool Colors::isEnabled() {
	return true;
}

void Colors::setEnabled(bool enabled) {
}

bool Colors::isVisible() {
	return false;
}