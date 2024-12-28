#pragma once

enum ActorFlags {
    OnFire,
    Sneaking,
    Riding,
    Sprinting,
    UsingItem,
    Invisible,
    Tempted,
    InLove,
    Saddled,
    Powered,
    /**
     * @deprecated typo.
     */
    Ignit0ed,
    Ignited = 0xa,
    Baby,
    Converting,
    Critical,
    CanShowName,
    AlwaysShowName,
    NoAI,
    Silent,
    WallClimbing,
    CanClimb,
    CanSwim,
    CanFly,
    CanWalk,
    Resting,
    Sitting,
    Angry,
    Interested,
    Charged,
    Tamed,
    Orphaned,
    Leashed,
    Sheared,
    Gliding,
    Elder,
    Moving,
    Breathing,
    Chested,
    Stackable,
    ShowBottom,
    Standing,
    Shaking,
    Idling,
    Casting,
    Charging,
    WasdControlled,
    CanPowerJump,
    Lingering,
    HasCollision,
    HasGravity,
    FireImmune,
    Dancing,
    Enchanted,
    ReturnTrident,
    ContainerIsPrivate,
    IsTransforming,
    DamageNearbyMobs,
    Swimming,
    Bribed,
    IsPregnant,
    LayingEgg,
    RiderCanPick,
    TransitionSitting,
    Eating,
    LayingDown,
    /**
     * @deprecated Typo!
     */
    Snezing,
    Sneezing = 0x40,
    Trusting,
    Rolling,
    Scared,
    InScaffolding,
    OverScaffolding,
    FallThroughScaffolding,
    DescendThroughBlock,
    Blocking,
    TransitionBlocking,
    BlockedUsingShield,
    BlockedUsingDamagedShield,
    Sleeping,
    WantsToWake,
    TradeInterest,
    DoorBreaker,
    BreakingObstruction,
    DoorOpener,
    IsIllagerCaptain,
    Stunned,
    Roaring,
    DelayedAttack,
    IsAvoidingMobs,
    IsAvoidingBlock,
    FacingTargetToRangeAttack,
    HiddenWhenInvisible,
    IsInUI,
    Stalking,
    Emoting,
    Celebrating,
    Admiring,
    CelebratingSpecial,
    OutOfControl,
    RamAttack,
    PlayingDead,
    InAscendableBlock,
    OverDescendableBlock,
};
