#pragma once
#include <regex>
#include "../BaseHook.h"

#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/Manager.h"

#include "../../../SDK/Render/MinecraftUIRenderContext.h"
#include "../../../SDK/Render/ScreenView.h"

class ScreenView__SetupAndRenderHook : public Hook {
public:
	static inline void* ScreenView__SetupAndRender;
	static inline void* MinecraftUIRenderContext__drawImage;
	static inline void* MinecraftUIRenderContext__drawText;

	static inline uintptr_t* renerCtxVTable = nullptr;

	static void MinecraftUIRenderContext__drawImageCallback(MinecraftUIRenderContext* renderCtx, TexturePtr* texturePtr, Vec2* pos, Vec2* size, Vec2* uvPos, Vec2* uvSize) {
		Memory::CallFunc<void, MinecraftUIRenderContext*, TexturePtr*, Vec2*, Vec2*, Vec2*, Vec2*>(
			MinecraftUIRenderContext__drawImage, renderCtx, texturePtr, pos, size, uvPos, uvSize);
	};
	static void MinecraftUIRenderContext__drawTextCallback(MinecraftUIRenderContext* renderCtx, class Font* font, const float* pos, std::string const& text, MC_Color const& color, float alpha, TextAlignment textAlignment, TextMeasureData const& textMeasureData, CaretMeasureData const& caretMeasureData) {
		std::string changed = text;
		changed = regex_replace(changed, (std::regex)Game.getLocalPlayer()->getNameTag(), std::string("Notch User"));

		Memory::CallFunc<void, MinecraftUIRenderContext*, Font*, const float*, std::string const&, MC_Color const&, float, TextAlignment, TextMeasureData const&, CaretMeasureData>(
			MinecraftUIRenderContext__drawText, renderCtx, font, pos, changed, color, alpha, textAlignment, textMeasureData, caretMeasureData);
	};
	static __int64 ScreenView__SetupAndRenderCallback(ScreenView* _this, MinecraftUIRenderContext* ctx) {
		//logF(StringUtil::combine("MUIRC Found at: ", (uintptr_t)(ctx + 0x0)), "INFO");
		//renerCtxVTable = *(uintptr_t**)(ctx);

		moduleMgr->onRender(ctx);
		return Memory::CallFunc<__int64, ScreenView*, MinecraftUIRenderContext*>(ScreenView__SetupAndRender, _this, ctx);
	};
	virtual void Initialize() override {
		Memory::CreateHook(getSig("ScreenView::SetupAndRender"), &ScreenView__SetupAndRenderCallback, &ScreenView__SetupAndRender, "ScreenView::SetupAndRender Hook");
		//while (renerCtxVTable == nullptr) Sleep(100);
		//Memory::CreateHook((void*)renerCtxVTable[7], &MinecraftUIRenderContext__drawImageCallback, &MinecraftUIRenderContext__drawImage, "MinecraftUIRenderContext::drawImage Hook");
		//Memory::CreateHook((void*)renerCtxVTable[5], &MinecraftUIRenderContext__drawTextCallback, &MinecraftUIRenderContext__drawText, "MinecraftUIRenderContext::drawText Hook");
	}
};