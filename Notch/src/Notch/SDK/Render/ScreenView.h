#pragma once
#include "../../Utils/Memory.h"
#include "../../Manager/Manager.h"
class ScreenView {
public:
	BUILD_ACCESS(this, class ScreenController*, screenController, 0x38);
	BUILD_ACCESS(this, class VisualTree*, visualTree, 0x8);
}; //Size: 0x0080