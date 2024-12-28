#pragma once
#include "Command.h"
#include "../../Config/ConfigManager.h"

class ConfigCommand : public Command {
public:
	ConfigCommand() : Command("config", "Load/save configs", "<load/save> <name>") {
		registerAlias("cfg");
		registerAlias("c");
	}

	~ConfigCommand() {
	}
	virtual bool execute(std::vector<std::string>* args) override {
		if (args->at(1) == "load" || args->at(1) == "l") {
			std::string name = args->at(2);
			configMgr->loadConfig(name);
			Game.getLocalPlayer()->displayClientMessage("%sSuccessfully loaded config %s%s%s!", GREEN, GRAY, configMgr->getCurrentConfig().c_str(), GREEN);
			return true;
		} else if (args->at(1) == "save" || args->at(1) == "s") {
			configMgr->saveConfig();
			Game.getLocalPlayer()->displayClientMessage("%sSuccessfully saved config %s%s%s!", GREEN, GRAY, configMgr->getCurrentConfig().c_str(), GREEN);
			return true;
		}
		else if (args->at(1) == "new" || args->at(1) == "n") {
			configMgr->setCurrentConfig(args->at(2));

			configMgr->saveConfig();
			Game.getLocalPlayer()->displayClientMessage("%sSuccessfully created config %s%s%s!", GREEN, GRAY, configMgr->getCurrentConfig().c_str(), GREEN);
			return true;
		}
		return false;
	}
};