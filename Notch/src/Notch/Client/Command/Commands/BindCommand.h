#pragma once
#include <map>
#include "Command.h"
#include "../../Module/ModuleManager.h"
#include "../../../Utils/Input.h"
#include "../../../Utils/TextFormat.h"

class BindCommand : public Command {
public:
	BindCommand() : Command("bind", "Binds modules to specific keys", "<module> <key>") {
		registerAlias("b");
	}

	~BindCommand() {
	}

	bool execute(std::vector<std::string>* args) {
		assertTrue(args->size() >= 2);
		std::string moduleName = args->at(1);
		assertTrue(moduleName.size() > 0);

		auto mod = moduleMgr->getModuleByName(moduleName);
		if (mod == nullptr) {
			Game.getLocalPlayer()->displayClientMessage("%sCould not find module with name: %s", RED, moduleName.c_str());
			return true;
		}
		if (args->size() >= 3) {
			std::string key = args->at(2);

			assertTrue(key.size() > 0);

			if (key.size() > 1) {
				std::transform(key.begin(), key.end(), key.begin(), ::tolower);
				const char* needle = key.c_str();

				if (key == "none") {
					mod->setKeybind(0x0);
					Game.getLocalPlayer()->displayClientMessage("%sSuccessfully unbound %s!", GREEN, mod->getModuleName());
					return true;
				}

				for (int i = 0; i < 190; i++) {
					const char* haystack = KeyNames[i];
					size_t len = strlen(needle) + 1;
					char* haystackLowercase = new char[len];
					for (int i = 0; i < len; i++)
						haystackLowercase[i] = tolower(haystack[i]);

					if (strcmp(needle, haystackLowercase) == 0) {
						mod->setKeybind(i);
						Game.getLocalPlayer()->displayClientMessage("%sThe keybind of %s is now '%s'", GREEN, mod->getModuleName(), haystack);
						delete[] haystackLowercase;
						return true;
					}
					delete[] haystackLowercase;
				}
				Game.getLocalPlayer()->displayClientMessage("%sInvalid key!", RED);
				return true;
			}

			int keyCode = (int)key.at(0);
			if (keyCode >= 0x61 && keyCode <= 0x7A)  // Convert key to lower case
				keyCode -= 0x20;

			if (keyCode >= 0x30 && keyCode <= 0x5A) {
				Module* mod = moduleMgr->getModuleByName(moduleName);
				if (mod == nullptr) {
					Game.getLocalPlayer()->displayClientMessage("%sCould not find module with name: %s", RED, moduleName.c_str());
				}
				else {
					mod->setKeybind(keyCode);
					Game.getLocalPlayer()->displayClientMessage("%sThe Keybind of %s is now '%c'", GREEN, mod->getModuleName(), keyCode);
				}
			}
			else {
				Game.getLocalPlayer()->displayClientMessage("%sInvalid Key! Outside of ascii range: %X", RED, keyCode);
			}
			return true;
		}
		else {
			Game.getLocalPlayer()->displayClientMessage("%s%s is currently bound to %s", RED, mod->getModuleName(), Utils::getKeybindName(mod->getKeybind()));
			return true;
		}

	}

};
