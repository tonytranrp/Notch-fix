#pragma once

#include "../BasePacket.h"
#include "../../../Utils/HMath.h"

class ActorEventPacket : public Packet {
public:
	enum class ActorEvent : int8_t {
		None = 0,
		Jump = 1,
		Hurt = 2,
		Death = 3,
		StartAttacking = 4,
		StopAttacking = 5,
		TamingFailed = 6,
		TamingSucceeded = 7,
		ShakeWetness = 8,
		EatGrass = 10,
		FishHookBubble = 11,
		FishHookFishpos = 12,
		FishHookHooktime = 13,
		FishHookTease = 14,
		SquidFleeing = 15,
		ZombieConverting = 16,
		PlayAmbientSound = 17,
		SpawnAlive = 18,
		StartOfferFlower = 19,
		StopOfferFlower = 20,
		LoveHearts = 21,
		VillagerAngry = 22,
		VillagerHappy = 23,
		WitchHatMagic = 24,
		FireworksExplode = 25,
		InLoveHearts = 26,
		SilverfishMergeAnim = 27,
		GuardianAttackSound = 27,
		DrinkPotion = 29,
		ThrowPotion = 30,
		PrimeTntcart = 31,
		PrimeCreeper = 32,
		AirSupply = 33,
		AddPlayerLevels = 34,
		GuardianMiningFatigue = 35,
		Agentswing = 36,
		DragonStartDeathAnim = 37,
		GroundDust = 38,
		Shake = 39,
		Feed = 57,
		BabyEat = 60,
		InstantDeath = 61,
		NotifyTrade = 62,
		LeashDestroyed = 63,
		CaravanUpdated = 64,
		TalismanActivate = 65,
		UpdateStructureFeature = 66,
		PlayerSpawnedMob = 67,
		DragonPuke = 68,
		UpdateStackSize = 69,
		StartSwimming = 70,
		BalloonPop = 71,
		TreasureHunt = 72,
		SummonAgent = 73,
		FinishedChargingCrossbow = 74,
		LandedOnGround = 75,
		GrowUp = 76,
	};

	ActorRuntimeID actorRuntimeId;
	ActorEvent eventId;
	int32_t data;

	ActorEventPacket() {
		static auto vtable = GetPacketVTable(PacketID::ActorEvent);
		this->vTable = vtable;
	}

	ActorEventPacket(const ActorRuntimeID& actorRuntimeId, ActorEvent eventId, int32_t data) : ActorEventPacket() {
		this->actorRuntimeId = actorRuntimeId;
		this->eventId = eventId;
		this->data = data;
	}
};