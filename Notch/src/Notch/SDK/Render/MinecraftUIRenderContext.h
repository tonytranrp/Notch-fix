#pragma once
#include "../../Utils/Memory.h"
#include "../../Utils/ColorUtil.h"
#include "TexturePtr.h"
#include "ScreenContext.h"
// horizontal alignment, there might be a way to align vertically??
enum class TextAlignment {
    // leading
    LEFT,
    // trailing
    RIGHT,
    CENTER,
};


struct TextMeasureData {
    float textSize = 10.f;
    float linePadding = 0.f;
    bool displayShadow = false;
    bool showColorSymbols = false;
    bool hideHyphen = false;

    constexpr TextMeasureData(float textSize, bool displayShadow, bool showColorSymbols)
        : textSize(textSize), displayShadow(displayShadow), showColorSymbols(showColorSymbols) {
    }
};

// A pointer to 0xFFFFFFFF by default
struct CaretMeasureData {
    int position = -1;
    bool shouldRender = false;
};


class MinecraftUIRenderContext {
public:
public:
    BUILD_ACCESS(this, uintptr_t, vtable, 0x0);
    BUILD_ACCESS(this, class ClientInstance*, clientinstance, 0x8);
    BUILD_ACCESS(this, ScreenContext*, screenContext, 0x10);
    BUILD_ACCESS(this, float, globalAlpha, 0x28);
    BUILD_ACCESS(this, class UIScene*, UIScene, 0xF0);

    void flushText(float lastFlush) {
        Memory::CallVFunc<void, float>(this, 6, lastFlush);
    }

    void drawImage(TexturePtr const& texture, Vec2 const& pos, Vec2 const& size, Vec2 const& uvPos, Vec2 const& uvSize) {
        Memory::CallVFunc<void, TexturePtr const&, Vec2 const&, Vec2 const&, Vec2 const&, Vec2 const&>(this, 7, texture, pos, size, uvPos, uvSize);
    }

    virtual ~MinecraftUIRenderContext() = 0; // 0x0
    virtual void getLineLength(class Font*, std::string const&, float, bool) = 0; // 0x1
    virtual float getTextAlpha() = 0; // 0x2
    virtual void setTextAlpha(float) = 0; // 0x3
    virtual void drawDebugText(Vec4 const&, std::string const&, MC_Color const&, float, TextAlignment, TextMeasureData const&, CaretMeasureData const&) = 0; // 0x4
    virtual void drawText(class Font* font, const float* pos, std::string const& text, MC_Color const& color, float alpha,  TextAlignment textAlignment, TextMeasureData const& textMeasureData, CaretMeasureData const& caretMeasureData) = 0; // 0x5

private:
    virtual void flushText_(float) = 0; // 0x6
    virtual void drawImage_(TexturePtr const& texture, Vec2 const& pos, Vec2 const& size, Vec2 const& uvPos, Vec2 const& uvSize) = 0; // 0x7
public:
    virtual void drawNineslice(TexturePtr const&, void* const&) = 0; // 0x8
    virtual void flushImages(MC_Color const&, float, class HashedString const&) = 0; // 0x9
    virtual void beginSharedMeshBatch(void*) = 0; // 0xA
    virtual void endSharedMeshBatch(void*) = 0; // 0xB
    virtual void drawRectangle(Vec4 const&, MC_Color const&, float, int) = 0; // 0xC
    virtual void fillRectangle(Vec4 const&, MC_Color const&, float) = 0; // 0xD
    virtual void increaseStencilRef() = 0; // 0xE
    virtual void decreaseStencilRef() = 0; // 0xF
    virtual void resetStencilRef() = 0; // 0x10
    virtual void fillRectangleStencil(Vec4 const&) = 0; // 0x11
    virtual void enableScissorTest(Vec4 const&) = 0; // 0x12
    virtual void disableScissorTest() = 0; // 0x13
    virtual void setClippingRectangle(Vec4 const&) = 0; // 0x14
    virtual void setFullClippingRectangle() = 0; // 0x15
    virtual void saveCurrentClippingRectangle() = 0; // 0x16
    virtual void restoreSavedClippingRectangle() = 0; // 0x17
    virtual Vec4 getFullClippingRectangle() = 0; // 0x18
    virtual void updateCustom(class CustomRenderComponent*) = 0; // 0x19
    virtual void renderCustom(class CustomRenderComponent*, int, Vec4 const&) = 0; // 0x1A
    virtual void cleanup() = 0; // 0x1B
    virtual void removePersistentMeshes() = 0; // 0x1C
    virtual TexturePtr* getTexture(TexturePtr* ptr, ResourceLocation const&, bool) = 0; // 0x1D
    virtual TexturePtr* getZippedTexture(TexturePtr* ptr, std::string const&, ResourceLocation const&, bool) = 0; // 0x1E
    virtual void unloadTexture(ResourceLocation const&) = 0; // 0x1F
    virtual void getUITextureInfo(ResourceLocation const&, bool) = 0; // 0x20
    virtual void touchTexture(ResourceLocation const&) = 0; // 0x21
    virtual void getMeasureStrategy() = 0; // 0x22
    virtual void snapImageSizeToGrid(Vec2&) = 0; // 0x23
    virtual void snapImagePositionToGrid(Vec2&) = 0; // 0x24
    virtual void notifyImageEstimate(unsigned long) = 0; // 0x25
};