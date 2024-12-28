#include "PotionHud.h"
#include <iomanip>

PotionHud::PotionHud() : Module("PotionHud", "Shows Your Effects Hud", Category::RENDER, 0x0) {
    addSlider<float>("Size", "Size of Text", &size, 0.f, 2.f);
    addSlider<int>("Padding", "Padding of Text Y", &padding, 0, 40);
    addSlider<float>("PosX", "Position X of Text", &Posi.x, 0.f, 1.f);
    addSlider<float>("PosY", "Position Y of Text", &Posi.y, 0.f, 1.f);
}

void PotionHud::onImGuiRender(ImDrawList* d) {
    if (!Game.getLocalPlayer() || !Game.canUseMoveKeys()) return;
    Vec2 winsize = Game.getGuiData()->realSize;
    float heightIncrement = 0;

    for (MobEffectInstance effect : Game.getLocalPlayer()->getMobEffectsComponent()->effects) {
        if ((int)effect.mId <= 0) continue;
        const int& totalSeconds = effect.mDuration / 20;
        const int& Hours = totalSeconds / 60 / 60;
        const int& Minutes = totalSeconds / 60;
        const int& Seconds = totalSeconds % 60;

        Vec2 RenderPos = Vec2(winsize.x * Posi.x, winsize.y * Posi.y);
        RenderPos.y += heightIncrement;
        UIColor col = EffectColors[(int)effect.mId];
        std::string EffectNameAndLevel = Effects[(int)effect.mId] + " " + Amplifiers[effect.mAmplifier + 1];
        ImGuiUtils::drawText(RenderPos, EffectNameAndLevel, col, size);
        std::ostringstream oss;
        oss << " "
            << std::setw(2) << std::setfill('0') << Minutes << ":"
            << std::setw(2) << std::setfill('0') << Seconds;
        std::string EffectTime = oss.str();
        ImGuiUtils::drawText(Vec2(RenderPos.x + ImGuiUtils::getTextWidth(EffectNameAndLevel, size), RenderPos.y), EffectTime, UIColor(255, 255, 255), size);

        heightIncrement += padding * size;
    }
}