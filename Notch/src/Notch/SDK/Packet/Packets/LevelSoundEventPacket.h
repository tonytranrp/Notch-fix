#pragma once

#include "../BasePacket.h"
#include "../../../Utils/HMath.h"

class LevelSoundEventPacket : public Packet {
public:
	LevelSoundEvent sound;
	Vec3 pos;
	int32_t extraData;
	std::string entityType;
	bool isBabyMob, isGlobal;

	LevelSoundEventPacket() : sound((LevelSoundEvent)0), pos({ 0.f, 0.f, 0.f }), extraData(-1), isBabyMob(false), isGlobal(false) {
		static auto vtable = GetPacketVTable(PacketID::LevelSoundEvent);
		this->vTable = vtable;
	}
	LevelSoundEventPacket(LevelSoundEvent sound, const Vec3& pos, int32_t extraData,
		const std::string& entityType, bool isBabyMob, bool isGlobal) : LevelSoundEventPacket() {
		this->sound = sound;
		this->pos = pos;
		this->extraData = extraData;
		this->entityType = entityType;
		this->isBabyMob = isBabyMob;
		this->isGlobal = isGlobal;
	}
};
