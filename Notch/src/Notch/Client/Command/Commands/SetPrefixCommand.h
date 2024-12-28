#pragma once
#include "Command.h"
#include "../Prefix.h"

class SetPrefixCommand :public Command {
public:
	SetPrefixCommand() : Command("setprefix", "Set the prefix for commands", "<prefix>") {
		registerAlias("prefix");
	}
	std::string cantUseChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	virtual bool execute(std::vector<std::string>* args) override {
		assertTrue(args->size() > 1);
		std::string prefix = args->at(1);
		for (auto Char : cantUseChars) {
			if (!prefix.starts_with(Char)) {
				prefixMgr->prefix = strdup(prefix.c_str());
				Game.getLocalPlayer()->displayClientMessage("%sSet prefix to %s%s", GREEN, GRAY, prefix);
			}
			else {
				Game.getLocalPlayer()->displayClientMessage("%sThat Prefix cannot be use %s(%sPrefix%s:%s%s%s)", RED, WHITE, RED, BLUE, GRAY, prefix, WHITE);
				return false;
			}
		}
		return true;
	};
};