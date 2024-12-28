#include "Camera.h"

Camera::Camera() : Module("Camera", "Camera Mod", Category::RENDER, 0x0) {
	addBoolCheck("ViewClip", "3rd-person in camera Clipping Blocks", &viewclip);
	addBoolCheck("Fullbright", "Modify your brightness/gamma.", &fullbright);
	addBoolCheck("MoreFov", "Modify your Field Of View.", &morefov);
	addSlider<int>("intensity", "intensity of Fullbright.", &intensity, 0, 25);
	addSlider<float>("Fov", "Customized Field Of View", &fov, 0.f, 179.9f);
};

void Camera::ClickGuiChanger() {
	if (fullbright) showSetting("intensity");
	else hideSetting("intensity");

	if (morefov) showSetting("Fov");
	else hideSetting("Fov");

}