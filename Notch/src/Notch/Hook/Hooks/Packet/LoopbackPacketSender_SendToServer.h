#pragma once
#include "../BaseHook.h"
#include "../../../GameData.h"
#include "../../../Client/Module/ModuleManager.h"
#include "../../../Client/Command/CommandManager.h"
#include "../../../Client/Command/Prefix.h"
#include "../../../SDK/ClientInstance/ClientInstance.h"
#include "../../../SDK/Packet/Packet.h"
class LoopbackPacketSender__SendToServerHook : public Hook {
public:
	static inline void* oSendToServer;
	static void SendToServerHook(LoopbackPacketSender* a1, Packet* a2) {
		std::string packetName = a2->getName().getText();
		if (packetName == "TextPacket") {
			TextPacket* funy = reinterpret_cast<TextPacket*>(a2);
			if (funy->message[0] == *prefixMgr->prefix) {
				char* Message = strdup(funy->message.c_str());
				cmdMgr->execute(Message);
				return;
			}
			else if (funy->message[0] == *".") {
				Game.getLocalPlayer()->displayClientMessage("%sYour prefix is: \"%s%c%s\"", RED, YELLOW, *prefixMgr->prefix, RED);
				Game.getLocalPlayer()->displayClientMessage("%sEnter \"%s%cprefix .%s\" to reset your prefix", RED, YELLOW, *prefixMgr->prefix, RED);
			}
		}
		return Memory::CallFunc<void, LoopbackPacketSender*, Packet*>(oSendToServer, a1, a2);
	}
	virtual void Initialize() override {
		while (Game.getClientInstance() == nullptr) Sleep(100);
		auto lps_vfTable = *(uintptr_t**)(Game.getClientInstance()->loopbackPacketSender);
		Memory::CreateHook((void*)lps_vfTable[2], &SendToServerHook, &oSendToServer, "LoopbackPacketSender::SendToServer Hook");
	}
};	