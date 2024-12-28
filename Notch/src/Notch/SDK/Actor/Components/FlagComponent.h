#pragma once

struct IEntityComponent {};

struct VerticalCollisionFlagComponent {};
struct HorizontalCollisionFlagComponent {};
struct WasOnGroundFlagComponent {};
struct JumpFromGroundRequestFlagComponent {};
struct LocalPlayerJumpRequestComponent {};
struct LocalPlayerComponent {};
struct ActorComponent {};
struct PlayerComponent {};
struct WasInWaterFlagComponent {};
struct WasInLavaFlagComponent {};
struct ActorIsImmobileFlagComponent {};
struct DiscardFrictionFlagComponent {};
struct CanStandOnSnowFlagComponent {};
struct OnGroundFlagComponent {};


template<typename T>
class FlagComponent {};

struct VerticalCollisionFlag {};
struct HorizontalCollisionFlag {};
struct WasOnGroundFlag {};
struct JumpFromGroundRequestFlag {};
struct LocalPlayerJumpRequestFlag {};
struct LocalPlayerComponentFlag {};
struct ActorFlag {};
struct PlayerComponentFlag {};
struct InWaterFlag {};
struct InLavaFlag {};
struct ActorIsImmobileFlag {};
struct DiscardFrictionFlag {};
struct CanStandOnSnowFlag {};