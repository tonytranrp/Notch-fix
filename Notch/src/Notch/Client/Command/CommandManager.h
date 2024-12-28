#pragma once
#include "../../GameData.h"
#include "Prefix.h"
#include <string>
#include "Commands/Command.h"
#include "Commands/SetPrefixCommand.h"
#include "Commands/ModulesCommand.h"
#include "Commands/ConfigCommand.h"
#include "Commands/CoordsCommand.h"
#include "Commands/UnbindCommand.h"
#include "Commands/EjectCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/BindCommand.h"

class CommandMgr {
public:
	~CommandMgr() {
		for (int i = 0; i < prefixMgr->commandList.size(); i++) {
			delete prefixMgr->commandList[i];
			prefixMgr->commandList[i] = nullptr;
		}
	};
	void initCommands() {
		prefixMgr->commandList.push_back(new SetPrefixCommand());
		prefixMgr->commandList.push_back(new ModulesCommand());
		prefixMgr->commandList.push_back(new ConfigCommand());
		prefixMgr->commandList.push_back(new CoordsCommand());
		prefixMgr->commandList.push_back(new UnbindCommand());
		prefixMgr->commandList.push_back(new EjectCommand());
		prefixMgr->commandList.push_back(new HelpCommand());
		prefixMgr->commandList.push_back(new BindCommand());
	};
	void execute(char* message) {
		if (message == nullptr) {
			return;
		}

		std::vector<std::string> args;
		std::string msgStr = message + 1;
		size_t pos = msgStr.find(" "), initialPos = 0;
		while (pos != std::string::npos) {
			args.push_back(msgStr.substr(initialPos, pos - initialPos));
			initialPos = pos + 1;
			pos = msgStr.find(" ", initialPos);
		}
		args.push_back(msgStr.substr(initialPos, std::min(pos, msgStr.size()) - initialPos + 1));
		std::string cmd = args[0];
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

		for (auto& c : prefixMgr->commandList) {
			auto aliases = c->getAliasList();
			for (const auto& alias : *aliases) {
				if (alias == cmd) {
					try {
						if (!c->execute(&args)) {
							Game.getLocalPlayer()->displayClientMessage("%s%sUsage: %s%c%s %s", RED, BOLD, RESET, *prefixMgr->prefix, c->getCommand(), c->getUsage(cmd.c_str()));
						}
					}
					catch (...) {
						Game.getLocalPlayer()->displayClientMessage("%s%sUsage: %s%c%s %s", RED, BOLD, RESET, *prefixMgr->prefix, c->getCommand(), c->getUsage(cmd.c_str()));
					}
					return;
				}
			}
		}

		Game.getLocalPlayer()->displayClientMessage("%sCommand '%s' could not be found!", RED, cmd.c_str());

		for (auto it = prefixMgr->commandList.begin(); it != prefixMgr->commandList.end(); ++it) {
			Command* c = *it;
			std::string commandCopy = c->getCommand();
			std::transform(commandCopy.begin(), commandCopy.end(), commandCopy.begin(), ::tolower);
			std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

			if (commandCopy.find(cmd) != std::string::npos)
				Game.getLocalPlayer()->displayClientMessage("%sDid you mean to type: %s?", RED, commandCopy.c_str());
		}
	}
};

extern CommandMgr* cmdMgr;