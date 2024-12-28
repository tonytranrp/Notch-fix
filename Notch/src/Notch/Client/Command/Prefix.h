#pragma once

#include "Commands/Command.h"
class PrefixManager {
public:
	static inline std::vector<Command*> commandList;
	static inline char* prefix = strdup(".");
	std::vector<Command*>* getCommandList() {
		return &commandList;
	}
};

extern PrefixManager* prefixMgr;