#pragma once

#include "../Module.h"
#include "../../../../SDK/Actor/Actor.h"
#include "../../../../GameData.h"
#include "../../../../Utils/ImGuiUtils.h"
#include <unordered_map>
#include <string.h>

class PotionHud : public Module {
public:
    float size = 1.f;
    int padding = 15;
    Vec2 Posi = Vec2(1.f, 1.f);
    PotionHud();
    virtual void onImGuiRender(ImDrawList* d) override;
private:
    std::unordered_map<int, std::string> Effects = {
        {static_cast<int>(MobEffectID::Speed), "Speed"},
        {static_cast<int>(MobEffectID::Slowness), "Slowness"},
        {static_cast<int>(MobEffectID::Haste), "Haste"},
        {static_cast<int>(MobEffectID::MiningFatigue), "Mining Fatigue"},
        {static_cast<int>(MobEffectID::Strength), "Strength"},
        {static_cast<int>(MobEffectID::InstantHealth), "Instant Health"},
        {static_cast<int>(MobEffectID::InstantDamage), "Instant Damage"},
        {static_cast<int>(MobEffectID::JumpBoost), "Jump Boost"},
        {static_cast<int>(MobEffectID::Nausea), "Nausea"},
        {static_cast<int>(MobEffectID::Regeneration), "Regeneration"},
        {static_cast<int>(MobEffectID::Resistance), "Resistance"},
        {static_cast<int>(MobEffectID::FireResistance), "Fire Resistance"},
        {static_cast<int>(MobEffectID::WaterBreathing), "Water Breathing"},
        {static_cast<int>(MobEffectID::Invisibility), "Invisibility"},
        {static_cast<int>(MobEffectID::Blindness), "Blindness"},
        {static_cast<int>(MobEffectID::NightVision), "Night Vision"},
        {static_cast<int>(MobEffectID::Hunger), "Hunger"},
        {static_cast<int>(MobEffectID::Weakness), "Weakness"},
        {static_cast<int>(MobEffectID::Poison), "Poison"},
        {static_cast<int>(MobEffectID::Wither), "Wither"},
        {static_cast<int>(MobEffectID::HealthBoost), "Health Boost"},
        {static_cast<int>(MobEffectID::Absorption), "Absorption"},
        {static_cast<int>(MobEffectID::Saturation), "Saturation"},
        {static_cast<int>(MobEffectID::Levitation), "Levitation"},
        {static_cast<int>(MobEffectID::FatalPoison), "Fatal Poison"},
        {static_cast<int>(MobEffectID::ConduitPower), "Conduit Power"},
        {static_cast<int>(MobEffectID::SlowFalling), "Slow Falling"},
        {static_cast<int>(MobEffectID::BadOmen), "Bad Omen"},
        {static_cast<int>(MobEffectID::VillageHero), "Village Hero"}
    };

    std::unordered_map<int, std::string> Amplifiers = {
        {1, "I"},
        {2, "II"},
        {3, "III"},
        {4, "IV"},
        {5, "V"},
        {6, "VI"},
        {7, "VII"},
        {8, "VIII"},
        {9, "IX"},
        {10, "X"},
    };

    std::unordered_map<int, UIColor> EffectColors = {
        {static_cast<int>(MobEffectID::Speed), UIColor(124, 175, 198)},          // Light Blue
        {static_cast<int>(MobEffectID::Slowness), UIColor(90, 108, 129)},        // Grayish Blue
        {static_cast<int>(MobEffectID::Haste), UIColor(217, 192, 67)},           // Yellow
        {static_cast<int>(MobEffectID::MiningFatigue), UIColor(74, 66, 23)},     // Brown
        {static_cast<int>(MobEffectID::Strength), UIColor(147, 36, 35)},         // Dark Red
        {static_cast<int>(MobEffectID::InstantHealth), UIColor(67, 10, 9)},      // Dark Red
        {static_cast<int>(MobEffectID::InstantDamage), UIColor(67, 10, 9)},      // Dark Red
        {static_cast<int>(MobEffectID::JumpBoost), UIColor(34, 255, 76)},        // Green
        {static_cast<int>(MobEffectID::Nausea), UIColor(85, 29, 74)},            // Dark Purple
        {static_cast<int>(MobEffectID::Regeneration), UIColor(205, 92, 171)},    // Pink
        {static_cast<int>(MobEffectID::Resistance), UIColor(153, 69, 58)},       // Brownish Red
        {static_cast<int>(MobEffectID::FireResistance), UIColor(228, 154, 58)},  // Orange
        {static_cast<int>(MobEffectID::WaterBreathing), UIColor(46, 82, 153)},   // Blue
        {static_cast<int>(MobEffectID::Invisibility), UIColor(127, 131, 146)},   // Gray
        {static_cast<int>(MobEffectID::Blindness), UIColor(31, 31, 35)},         // Dark Gray
        {static_cast<int>(MobEffectID::NightVision), UIColor(31, 31, 161)},      // Dark Blue
        {static_cast<int>(MobEffectID::Hunger), UIColor(88, 118, 83)},           // Greenish Brown
        {static_cast<int>(MobEffectID::Weakness), UIColor(72, 77, 72)},          // Gray
        {static_cast<int>(MobEffectID::Poison), UIColor(78, 147, 49)},           // Green
        {static_cast<int>(MobEffectID::Wither), UIColor(53, 42, 39)},            // Dark Brown
        {static_cast<int>(MobEffectID::HealthBoost), UIColor(248, 125, 35)},     // Orange
        {static_cast<int>(MobEffectID::Absorption), UIColor(37, 82, 165)},       // Blue
        {static_cast<int>(MobEffectID::Saturation), UIColor(248, 36, 35)},       // Red
        {static_cast<int>(MobEffectID::Levitation), UIColor(206, 255, 255)},     // Light Cyan
        {static_cast<int>(MobEffectID::FatalPoison), UIColor(0, 85, 0)},        // Dark Green
        {static_cast<int>(MobEffectID::ConduitPower), UIColor(0, 255, 255)},    // Aqua
        {static_cast<int>(MobEffectID::SlowFalling), UIColor(255, 255, 255)},   // White
        {static_cast<int>(MobEffectID::BadOmen), UIColor(0, 64, 64)},           // Dark Teal
        {static_cast<int>(MobEffectID::VillageHero), UIColor(85, 170, 85)}      // Green
    };
};