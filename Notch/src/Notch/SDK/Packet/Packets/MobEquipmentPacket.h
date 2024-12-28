#pragma once

#include "../BasePacket.h"
#include "../../../Utils/HMath.h"

//class MobEquipmentPacket : public Packet {
//public:
//	MobEquipmentPacket() {
//		static auto vtable = GetPacketVTable(PacketID::MobEquipment);
//		this->vTable = vtable;
//	}
//
//	ActorRuntimeID actorRuntimeId;
//	ItemStack item;
//	int32_t inventorySlot;
//	int32_t hotbarSlot;
//	ContainerID containerId;
//};