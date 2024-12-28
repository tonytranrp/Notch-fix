#pragma once
#include "../Module.h"
#include "../../../../Utils/ColorUtil.h"
#include "../../../../Utils/TimeUtil.h"
#include "../../ModuleManager.h"


class Test : public Module {
public:
    
	Test();
	virtual void onEnable() override;
	virtual void onDisable() override;
};