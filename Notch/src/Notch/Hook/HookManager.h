#pragma once
#include <iostream>
#include <vector>
#include <thread>

#include "Hooks/BaseHook.h"

class HookManager {
public:
	static bool initalize;

	static void init();
	static Hook* getHook(Hook* other);
	static void initImGui();
	static void RestoreImGui();

	static inline std::vector<Hook*> Hooks;
};