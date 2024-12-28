#pragma once
#include <Windows.h>
#include <cstdarg>
#include "PacketID.h"
#include "PacketHandlerDispatcherInstance.h"
#include "../../Utils/Memory.h"
#include "../../Manager/Manager.h"
#include "../Misc/TextHolder.h"

class ConnectionRequest;
class ContainerID {};
class ActorRuntimeID {};
enum class LevelSoundEvent : int32_t;

union PacketHeader {
	struct {
		uint32_t packetId : 10;
		uint32_t recipientSubId : 2;
		uint32_t senderSubId : 2;
	};
	uint32_t packed;
};
static_assert(sizeof(PacketHeader) == 0x4);
class MinecraftPackets {
public:
	static std::shared_ptr<class Packet> createPacket(PacketID packetId) {
		using createPacket = std::shared_ptr<class Packet>(__cdecl*)(int);
		static createPacket createPacketFunc = 0x0;
		if (!createPacketFunc) createPacketFunc = (createPacket)(uintptr_t)getSig("MinecraftPackets::createPacket");
		return createPacketFunc(static_cast<int>(packetId));
	}
};

class Packet {
public:
	BUILD_ACCESS(this, uintptr_t**, vTable, 0x0);
public:
	int32_t priority = 2;
	int32_t reliability = 1;
	uint8_t subClientId = 0;
	bool isHandled = false;
	void* unknown = nullptr;
	PacketHandlerDispatcherInstance* handler = nullptr;
	int32_t compressibility = 0;
public:
	uintptr_t** GetPacketVTable(PacketID id) {
		auto packet = MinecraftPackets::createPacket(id);
		return packet.get()->vTable;
	}
public:
	virtual void packetConstructor(void) {};
	virtual PacketID getId(void) { return (PacketID)0x0; };
	virtual TextHolder getName() { return (TextHolder)nullptr; };
	virtual void write(class BinaryStream&) {};
	virtual void read(class ReadOnlyBinaryStream&) {};
	virtual void readExtended(class ReadOnlyBinaryStream&) {};
	virtual void disallowBatching(void) {};
};