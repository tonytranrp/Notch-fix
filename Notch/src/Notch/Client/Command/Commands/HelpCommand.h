#pragma once
#include "Command.h"
#include "../Prefix.h"
class HelpCommand : public Command {
public:
	HelpCommand() : Command("help", "Lists all commands", "") {
		registerAlias("h");
	}

	~HelpCommand() {
	}
	// Inherited via Command
	virtual bool execute(std::vector<std::string>* args) override {
		Game.getLocalPlayer()->displayClientMessage("==========");
		std::vector<Command*>* commandList = prefixMgr->getCommandList();
		for (auto it = commandList->begin(); it != commandList->end(); ++it) {
			Command* plump = *it;
			Game.getLocalPlayer()->displayClientMessage("%s%s - %s%s", plump->getCommand(), GRAY, ITALIC, plump->getDescription());
		}
		Game.getLocalPlayer()->displayClientMessage("==========");
		return true;
	};
};
