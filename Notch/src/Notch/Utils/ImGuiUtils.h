#pragma once
#include <string>
#include <vector>
#include "ColorUtil.h"
#include "HMath.h"
#include "../Libraries/Libs/ImGui/imgui.h"
#include "../Client/Module/ModuleManager.h"

class ImGuiUtils {
private:
	static inline ImDrawList* drawlist = nullptr;
	static inline float fontSize = 25.f; // 22.f
	static inline float shadowOffset = 1.f;
public:
	static void setDrawList(ImDrawList* d);
	static void drawText(Vec2 textPos, std::string textStr, UIColor color, float textSize = 1.f, bool shadow = true);
	static void setFontSize(float newSize) { fontSize = newSize; };
	static void setShadowOffset(float offset) { shadowOffset = offset; }
	static float getTextWidth(std::string textStr, float textSize = 1.f);
	static float getTextHeight(float textSize = 1.f);
	static void drawRectangle(const Vec4& rectPos, UIColor color, float lineWidth = 1.0f, float rounding = 0.0f, ImDrawFlags flags = 0);
	static void drawRectangle(Vec2 pMin, Vec2 pMax, UIColor color, float lineWidth = 1.0f, float rounding = 0.0f, ImDrawFlags flags = 0);
	static void fillRectangle(Vec4 rectPos, UIColor color, float rounding = 0.0f, ImDrawFlags flags = 0);
	static void fillRectangle(Vec2 pMin, Vec2 pMax, UIColor color, float rounding = 0.0f, ImDrawFlags flags = 0);

	static void drawTextCenter(Vec2 centerPos, std::string textStr, UIColor color, float textSize = 1.f, bool shadow = true);
	static void drawTextCenterY(Vec2 centerPos, std::string textStr, UIColor color, float textSize = 1.f, bool shadow = true, float addX = 0.f);

	static void drawTextCenter4(Vec4 centerRect, std::string textStr, UIColor color, float textSize = 1.f, bool shadow = true);
	/* vec4 only centered Y/W */static void drawTextCenter4Y(Vec4 centerRect, std::string textStr, UIColor color, float textSize = 1.f, bool shadow = true, float add = 0.f);


	static void drawBox(const AABB& blockAABB, UIColor color, UIColor lineColor, float lineWidth, bool fill, bool outline);
	static void drawBox(const Vec3& blockPos, UIColor color, UIColor lineColor, float lineWidth, bool fill, bool outline);
	static bool worldToScreen(const Vec3& pos, Vec2& out);
};