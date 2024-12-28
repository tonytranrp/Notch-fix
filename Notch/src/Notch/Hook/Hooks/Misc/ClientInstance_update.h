#pragma once
#include "../BaseHook.h"
#include "../../../Utils/Memory.h"
#include "../../../Manager/Manager.h"

#include "../../../Notch.h"
class ClientInstance__updateHook : public Hook {
public:
	static inline void* oClientInstanceUpdate;
	static bool ClientInstanceUpdateCallback(ClientInstance* ci, bool isinitFinished) {
		Game.clientinstance = ci;
		return Memory::CallFunc<bool, ClientInstance*, bool>(oClientInstanceUpdate, ci, isinitFinished);
	};

	virtual void Initialize() override {
		Memory::CreateHook(getSig("ClientInstance::update"), (void*)&ClientInstanceUpdateCallback, &oClientInstanceUpdate, xorstr_("ClientInstance::update Hook"));
	}
};