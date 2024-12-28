#pragma once
#include <map>

#include "Command.h"

class UnbindCommand : public Command {
public:
	UnbindCommand() : Command("unbind", "unbind modules", "<module | all>") {
		registerAlias("ub");
	}

    ~UnbindCommand() {
	}

	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override {
		assertTrue(args->size() >= 2);
		std::string moduleName = args->at(1);

		assertTrue(moduleName.size() > 0);

		if (moduleName == "all") {
			if (args->size() >= 3 && args->at(2) == "force") {
				std::vector<Module*>* modules = moduleMgr->getModuleList();
				for (auto it = modules->begin(); it != modules->end(); ++it) {
					auto mod = *it;
					mod->setKeybind(0x0);
				}
				Game.getLocalPlayer()->displayClientMessage("%sUnbound all modules!", YELLOW);
			}
			else {
				Game.getLocalPlayer()->displayClientMessage("%sAre you sure? This will unbind %sALL%s modules!", RED, BOLD, RESET, RED);
				Game.getLocalPlayer()->displayClientMessage("%sUse %s.unbind all force%s to unbind all modules", RED, WHITE, RED);
			}
			return true;
		}

		auto mod = moduleMgr->getModuleByName(moduleName);
		if (mod == nullptr) {
			Game.getLocalPlayer()->displayClientMessage("%sCould not find module with name: %s", RED, moduleName.c_str());
			return true;
		}

		mod->setKeybind(0x0);
		Game.getLocalPlayer()->displayClientMessage("%sSuccessfully unbound %s!", GREEN, mod->getModuleName());
		return true;
	};
};
