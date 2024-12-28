#pragma once
#include "../BaseHook.h"
#include "../../../Utils/Memory.h"
#include "../../../Manager/Manager.h"
#include "../../../Utils/ColorUtil.h"

#include "glm\glm\vec2.hpp"
class Font__drawTransformedHook : public Hook {
public:
    static inline void* odrawTransformedHook;
    static void drawTransformedDetour(void* _this, void* screenContext, const std::string* str, float x, float y, const MC_Color* color, float angle, float size, bool centered, float maxWidth, bool shadow, const MC_Color* shadowColor, const glm::tvec2<float>* shadowOffset) {
        std::string notPtroverwrite_str = "Notch Client!";
        MC_Color notPtroverwrite_color = MC_Color(0.58f, 0.83f, 1.f);
        const std::string* overwrite_str = &notPtroverwrite_str;
        const MC_Color* overwrite_color = &notPtroverwrite_color;
        return Memory::CallFunc<void, void*, void*, const std::string*, float, float, const MC_Color*, float, float, bool, float, bool, const MC_Color*, const glm::tvec2<float>*>(odrawTransformedHook, _this, screenContext, overwrite_str, x, y, overwrite_color, angle, size * 1.2f, centered, maxWidth, shadow, shadowColor, shadowOffset);
    };
    virtual void Initialize() override {
        Memory::CreateHook(getSig("Font::drawTransformed"), (void*)&drawTransformedDetour, &odrawTransformedHook, "Font::drawTransformed Hook");
    }
};