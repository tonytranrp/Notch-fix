#pragma once
#include "Command.h"
#include "../../../GameData.h"
#include <vector>
#include <iostream>
class EjectCommand : public Command {
public:
	EjectCommand() : Command("eject", "Removes the cheat from the game.", "") {
		registerAlias("uninject");
		registerAlias("uni");
		registerAlias("ui");
		registerAlias("uinject");
	}

	~EjectCommand() {
	}

	virtual bool execute(std::vector<std::string>* args) override {
		Game.uninject();
		return true;
	}

};
