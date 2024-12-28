#pragma once

#include "../BasePacket.h"
#include "../../../Utils/HMath.h"
class InteractPacket : public Packet {
public:
	enum class Action : int8_t {
		StopRiding = 3,
		InteractUpdate = 4,
		NpcOpen = 5,
		OpenInventory = 6,
	};

	InteractPacket() {
		static auto vtable = GetPacketVTable(PacketID::Interact);
		this->vTable = vtable;
	}
	InteractPacket(Action action, ActorRuntimeID actorRuntimeId, Vec3 pos) : InteractPacket() {
		this->action = action;
		this->actorRuntimeId = actorRuntimeId;
		this->pos = pos;
	}

	Action action;
	ActorRuntimeID actorRuntimeId;
	Vec3 pos;
};