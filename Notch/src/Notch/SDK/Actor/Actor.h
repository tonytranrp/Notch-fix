 #pragma once

#include "../../Utils/HMath.h"
#include "../../Utils/ColorUtil.h"
#include "../../Utils/TextFormat.h"
#include "../../Manager/Manager.h"
#include "../../Utils/Memory.h"
#include "GameMode.h"
#include "GameType.h"
#include "ActorDefinitionIdentifier.h"
#include "MobEffectInstance.h"
#include "../Attribute/Attribute.h"
#include "../Attribute/BaseAttributeMap.h"
#include "Components/AttributesComponent.h"
#include "Components/ActorDefinitionIdentifierComponent.h"
#include "Components/ActorTypeComponent.h"
#include "Components/ActorGameTypeComponent.h"
#include "Components/ActorUniqueIDComponent.h"
#include "Components/JumpComponent.h"
#include "Components/RuntimeIDComponent.h"
#include "Components/DepenetrationComponent.h"
#include "Components/StateVectorComponent.h"
#include "Components/AABBShapeComponent.h"
#include "Components/ActorEquipmentComponent.h"
#include "Components/ActorHeadRotationComponent.h"
#include "Components/ActorRotationComponent.h"
#include "Components/BlockMovementSlowdownMultiplierComponent.h"
#include "Components/FallDistanceComponent.h"
#include "Components/MaxAutoStepComponent.h"
#include "Components/MobHurtTimeComponent.h"
#include "Components/MobBodyRotationComponent.h"
#include "Components/RenderPositionComponent.h"
#include "Components/MoveInputComponent.h"
#include "Components/MovementInterpolatorComponent.h"
#include "Components/MobEffectsComponent.h"
#include "Components/FlagComponent.h"
#include "../Level/Level.h"
#include "../Item/PlayerInventory.h"
#include <bitset>
#include "ActorFlags.h"

#include "EntityID.h"
#include "EntityContext.h"

class Actor {
public:
	BUILD_ACCESS(this, Level*, level, getOffset("Actor::level"));
	BUILD_ACCESS(this, StateVectorComponent*, StateVector, getOffset("Actor::getPosition"));
	BUILD_ACCESS(this, AABBShapeComponent*, AABBShape, getOffset("Actor::getAABB"));
	BUILD_ACCESS(this, MovementInterpolatorComponent*, MovementInterpolator, getOffset("Actor::getRotation"));
public:
	virtual bool getStatusFlag(ActorFlags) const; // 0
	virtual void setStatusFlag(ActorFlags, bool); // 1
public:
	EntityContext* getEntityContext() {
		uintptr_t address = reinterpret_cast<uintptr_t>(this);
		return reinterpret_cast<EntityContext*>((uintptr_t)this + 0x8);
	}
	template <typename T>
	T* getComponent() {
		return const_cast<T*>(getEntityContext()->getRegistry().try_get<T>(getEntityContext()->mEntity));
	}

	template <typename T>
	bool hasComponent() {
		return getEntityContext()->getRegistry().all_of<T>(getEntityContext()->mEntity);
	}

	template <typename T>
	void getOrEmplaceComponent() {
		return getEntityContext()->getRegistry().get_or_emplace<T>(getEntityContext()->mEntity);
	}

	template <typename T>
	void removeComponent() {
		getEntityContext()->getRegistry().remove<T>(getEntityContext()->mEntity);
	}


	std::string getNameTag() {
		return *Memory::CallFunc<std::string*, void*>(getSig("Actor::getNameTag"), (void*)this);
	}
	
	void playEmote(const std::string pieceID, bool Message) {
		Memory::CallFunc<void, Actor*, const std::string, bool>(getSig("Actor::playEmote"), this, pieceID, Message);
	};

	Vec3 getPosition() {
		return this->getStateVector()->Position;
	};
	Vec3 getPositionOld() {
		return this->getStateVector()->PrevPosition;
	};
	AttributesComponent* getAttributesComponent() {
		return getComponent<AttributesComponent>();
	}
	bool isInLava() {
		if (Manager::checkVer(Manager::targetVersions1_21_X))
			return hasComponent<FlagComponent<InLavaFlag>>();
		else if (Manager::checkVer(Manager::targetVersions1_21_2X) || Manager::checkVer(Manager::targetVersions1_21_3X))
			return hasComponent<WasInLavaFlagComponent>();
	}

	bool isInWater() {
		if (Manager::checkVer(Manager::targetVersions1_21_X))
			return hasComponent<FlagComponent<InWaterFlag>>();
		else if (Manager::checkVer(Manager::targetVersions1_21_2X) || Manager::checkVer(Manager::targetVersions1_21_3X))
			return hasComponent<WasInWaterFlagComponent>();
	}

	bool isImmobile() {
		if (Manager::checkVer(Manager::targetVersions1_21_X))
			return hasComponent<FlagComponent<ActorIsImmobileFlag>>();
		else if (Manager::checkVer(Manager::targetVersions1_21_2X) || Manager::checkVer(Manager::targetVersions1_21_3X))
			return hasComponent<ActorIsImmobileFlagComponent>();
	}

	void setImmobile(bool state) {
		if (Manager::checkVer(Manager::targetVersions1_21_X)) {
			if (state) { getOrEmplaceComponent<FlagComponent<ActorIsImmobileFlag>>(); }
			else { removeComponent<FlagComponent<ActorIsImmobileFlag>>(); }
		}
		else if (Manager::checkVer(Manager::targetVersions1_21_2X) || Manager::checkVer(Manager::targetVersions1_21_3X)) {
			if (state) { getOrEmplaceComponent<ActorIsImmobileFlagComponent>(); }
			else { removeComponent<ActorIsImmobileFlagComponent>(); }
		};
	}

	bool isOnGround() {
		return hasComponent<OnGroundFlagComponent>();
	}

	void setIsOnGround(bool state) {
		if (state) { getOrEmplaceComponent<OnGroundFlagComponent>(); }
		else { removeComponent<OnGroundFlagComponent>(); }
	};

	void jumpFromGround() {
		if (Manager::checkVer(Manager::targetVersions1_21_X))
			getOrEmplaceComponent<FlagComponent<JumpFromGroundRequestFlag>>();
		else if (Manager::checkVer(Manager::targetVersions1_21_2X) || Manager::checkVer(Manager::targetVersions1_21_3X))
			getOrEmplaceComponent<JumpFromGroundRequestFlagComponent>();
	}

	AttributeInstance* getAttribute(int id) {
		auto& map = getAttributesComponent()->baseAttributeMap.attributes;
		auto it = map.find(id);
		if (it != map.end()) {
			return &it->second;
		}
		return nullptr;
	}
	AttributeInstance* getAttribute(AttributeId id) {
		return getAttribute((int)id);
	}

	bool isPlayer() {
		if (Manager::checkVer(Manager::targetVersions1_21_X))
			return hasComponent<FlagComponent<PlayerComponentFlag>>();
		else if (Manager::checkVer(Manager::targetVersions1_21_2X) || Manager::checkVer(Manager::targetVersions1_21_3X))
			return hasComponent<PlayerComponent>();
	}

	bool isLocalPlayer() {
		if (Manager::checkVer(Manager::targetVersions1_21_X))
			return hasComponent<FlagComponent<LocalPlayerComponentFlag>>();
		else if (Manager::checkVer(Manager::targetVersions1_21_2X) || Manager::checkVer(Manager::targetVersions1_21_3X))
			return hasComponent<LocalPlayerComponent>();
	}

	float getFallDistance() {
		return getComponent<FallDistanceComponent>()->fallDistance;
	}

	void setFallDistance(float distance) {
		getComponent<FallDistanceComponent>()->fallDistance = distance;
	}
	MoveInputComponent* getMoveInputHandler() {
		return getComponent<MoveInputComponent>();
	}
	int32_t getHurtTime() {
		return getComponent<MobHurtTimeComponent>()->hurtTime;
	}
	float getAbsorption() {
		return getAttribute(AttributeId::Absorption)->currentValue;
	}

	float getHealth() {
		return getAttribute(AttributeId::Health)->currentValue;
	}

	int64_t getRuntimeID() {
		return getComponent<RuntimeIDComponent>()->runtimeID;
	}

	int64_t getUniqueID() {
		return getComponent<ActorUniqueIDComponent>()->uniqueID;
	}

	Vec3 getRenderPosition() {
		return getComponent<RenderPositionComponent>()->renderPos;
	}


	virtual void lerpMotion(Vec3 motionVector) {
		this->getStateVector()->Velocity.x = motionVector.x;
		this->getStateVector()->Velocity.y = motionVector.y;
		this->getStateVector()->Velocity.z = motionVector.z;
	}
	Level* getLevel() {
		return this->level;
	}
	MobEffectsComponent* getMobEffectsComponent() {
		return getComponent<MobEffectsComponent>();
	}
	void swing() {
		Memory::CallVFunc<void>(this, getIndex("Actor::swing"));
	}
};

class Player : public Actor {
public:
	BUILD_ACCESS(this, GameMode*, gamemode, getOffset("Player::gamemode"));
	BUILD_ACCESS(this, PlayerInventory*, Supplies, getOffset("Player::getSupplies"));

	GameMode* getGameMode() {
		return this->gamemode;
	}
	void displayClientMessage(std::string Message, ...) {
		va_list arg;
		va_start(arg, Message.c_str());
		char message[400];
		vsprintf_s(message, 400, Message.c_str(), arg);
		std::string* MessagePointer = new std::string(std::string(BOLD) + std::string(BLACK) + "[" + std::string(AQUA) + "Notch" + std::string(BLACK) + "] " + std::string(RESET) + message);
		std::optional<std::string> opt = {};
		if (Manager::checkVer(Manager::targetVersions1_21_X)) Memory::CallVFunc<void, std::string*>((void*)this, getIndex("ServerPlayer::displayClientMessage"), MessagePointer);
		else if (Manager::checkVer(Manager::targetVersions1_21_2X) || Manager::checkVer(Manager::targetVersions1_21_3X)) Memory::CallVFunc<void, std::string*>((void*)this, getIndex("ServerPlayer::displayClientMessage"), MessagePointer, opt);
	};
};

class LocalPlayer : public Player {
public:
};