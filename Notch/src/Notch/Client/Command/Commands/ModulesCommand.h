#pragma once
#include "Command.h"
#include "../../Module/ModuleManager.h"
class ModulesCommand : public Command {
public:
	ModulesCommand() : Command("modules", "Lists all modules", "") {
		registerAlias("mods");
	}
	~ModulesCommand() {
	}
	virtual bool execute(std::vector<std::string>* args) override {
		std::vector<Module*>* modules = moduleMgr->getModuleList();
		Game.getLocalPlayer()->displayClientMessage("==========");
		Game.getLocalPlayer()->displayClientMessage("Modules (%i):", modules->size());
		for (auto it = modules->begin(); it != modules->end(); ++it) {
			auto mod = *it;
			Game.getLocalPlayer()->displayClientMessage("%s %s- %s%s", mod->getModuleName(), GRAY, ITALIC, mod->getDescription());
		}

		return true;
	};
};
