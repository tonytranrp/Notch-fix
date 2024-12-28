#pragma once

#include "../BasePacket.h"
#include "../../../Utils/HMath.h"

class PlayerActionPacket : public Packet {
public:
	enum class Action {
		StartBreakBlock = 0,
		AbortBreakBlock,
		StopBreakBlock,
		GetUpdatedBlock,
		DropItem,
		StartSleeping,
		StopSleeping,
		Respawn,
		Jump,
		StartSprint,
		StopSprint,
		StartSneak,
		StopSneak,
		CreativePlayerDestroyBlock,
		DimensionChangeDone,
		StartGlide,
		StopGlide,
		BuildDenied,
		CrackBlock, // ???
		ChangeSkin,
		SetEnchantmentSeed,
		StartSwimming,
		StopSwimming,
		StartSpinAttack,
		StopSpinAttack,
		StartBuildingBlock,
		PredictDestroyBlock,
		ContinueDestroyBlock,
		StartItemUseOn,
		StopItemUseOn,
	};

	PlayerActionPacket() {
		static auto vtable = GetPacketVTable(PacketID::PlayerAction);
		this->vTable = vtable;
	}

	Vec3 blockPosition;
	Vec3 resultPosition;
	int32_t face;
	Action action;
	ActorRuntimeID actorRuntimeId;
};