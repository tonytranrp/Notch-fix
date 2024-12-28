#pragma once

#include <stack>
#include "../../Utils/Memory.h"
#include "../../Utils/ColorUtil.h"

class ScreenContext {
public:
	BUILD_ACCESS(this, MC_Color*, shaderColor, 0x30);
	BUILD_ACCESS(this, class Tessellator*, tess, 0xC0);

	BUILD_ACCESS(this, class MatrixPtr*, matrix, 0x18);

	inline static ScreenContext* instance3d = nullptr;
};