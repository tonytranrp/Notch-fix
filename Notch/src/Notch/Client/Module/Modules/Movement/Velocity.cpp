#include "Velocity.h"

Velocity::Velocity() : Module("Velocity", "You dont take knockback.", Category::MOVEMENT, 0x0) {
	addSlider<float>("XZ Modifier", "Changes x & z velocity.", &xModifier, 0.f, 1.f);
	addSlider<float>("Y Modifier", "Changes y velocity.", &yModifier, 0.f, 1.f);
}

Velocity::~Velocity() {
};