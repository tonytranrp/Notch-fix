#pragma once
#include "Command.h"
#include "../../../GameData.h"
#include <vector>
#include <iostream>
class CoordsCommand : public Command {
public:
	CoordsCommand() : Command("coords", "Prints your coordinates", "") {
		registerAlias("pos");
		registerAlias("position");
	}

	~CoordsCommand() {
	}

	virtual bool execute(std::vector<std::string>* args) {
		Vec3 pos = Game.getLocalPlayer()->getPosition();
		Game.getLocalPlayer()->displayClientMessage("%sX: %i Y: %i Z: %i", GREEN, (int)pos.x, (int)pos.y, (int)pos.z);
		
		return true;
	}

};
