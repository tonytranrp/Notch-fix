#pragma once

#pragma comment(lib, "runtimeobject")
#include "../../Libraries/Libs/Json.hpp"
#include "../Module/ModuleManager.h"
#include "../Command/prefix.h"

#include "../System/FileSystem.h"

using json = nlohmann::json;

class ConfigManager {
private:
	std::string currentConfig = xorstr_("default");
	json currentConfigObj;
public:
	std::string getCurrentConfig() {
		return currentConfig;
	}
	void setCurrentConfig(std::string configName) {
		currentConfig = configName;
	}
	void saveConfig();
	void loadConfig(std::string configName);
};

extern ConfigManager* configMgr;