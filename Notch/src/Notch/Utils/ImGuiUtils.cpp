#include "ImGuiUtils.h"

#include "../GameData.h"

void ImGuiUtils::setDrawList(ImDrawList* d) {
	drawlist = d;
}

void ImGuiUtils::drawText(Vec2 textPos, std::string textStr, UIColor color, float textSize, bool shadow) {
	static CustomFont* cFontMod = moduleMgr->getModule<CustomFont>();
	if (cFontMod->fontShadow && shadow) drawlist->AddText(nullptr, fontSize * textSize, textPos.add(shadowOffset * textSize).toImVec2(), ImColor((int)(color.r / 5.f), (int)(color.g / 5.f), (int)(color.b / 5.f), color.a), textStr.c_str());
	drawlist->AddText(nullptr, fontSize * textSize, textPos.toImVec2(), color.toImColor(), textStr.c_str());
}
float ImGuiUtils::getTextWidth(std::string textStr, float textSize) {
	return ImGui::GetFont()->CalcTextSizeA(fontSize * textSize, FLT_MAX, -1, textStr.c_str()).x;
}

float ImGuiUtils::getTextHeight(float textSize) {
	return ImGui::GetFont()->CalcTextSizeA(fontSize * textSize, FLT_MAX, -1, "").y;
}

void ImGuiUtils::drawRectangle(const Vec4& rectPos, UIColor color, float lineWidth, float rounding, ImDrawFlags flags) {
	drawlist->AddRect(ImVec2(rectPos.x, rectPos.y), ImVec2(rectPos.z, rectPos.w), color.toImColor(), rounding, flags, lineWidth);
}

void ImGuiUtils::drawRectangle(Vec2 pMin, Vec2 pMax, UIColor color, float lineWidth, float rounding, ImDrawFlags flags) {
	drawlist->AddRect(pMax.toImVec2(), pMax.toImVec2(), color.toImColor(), rounding, flags, lineWidth);
}

void ImGuiUtils::fillRectangle(Vec4 rectPos, UIColor color, float rounding, ImDrawFlags flags) {
	drawlist->AddRectFilled(ImVec2(rectPos.x, rectPos.y), ImVec2(rectPos.z, rectPos.w), color.toImColor(), rounding, flags);
}

void ImGuiUtils::fillRectangle(Vec2 pMin, Vec2 pMax, UIColor color, float rounding, ImDrawFlags flags) {
	drawlist->AddRectFilled(pMin.toImVec2(), pMax.toImVec2(), color.toImColor(), rounding, flags);
}

void ImGuiUtils::drawTextCenter(Vec2 centerPos, std::string textStr, UIColor color, float textSize, bool shadow)
{
	drawText(centerPos.sub(Vec2(ImGuiUtils::getTextWidth(textStr, textSize) / 2, ImGuiUtils::getTextHeight(textSize) / 2)), textStr, color, textSize, shadow);
}

void ImGuiUtils::drawTextCenterY(Vec2 centerPos, std::string textStr, UIColor color, float textSize, bool shadow, float addX)
{
	drawText(Vec2(centerPos.x + addX, centerPos.y - (ImGuiUtils::getTextHeight(textSize) / 2)), textStr, color, textSize, shadow);
}

void ImGuiUtils::drawTextCenter4(Vec4 centerRect, std::string textStr, UIColor color, float textSize, bool shadow)
{
	Vec2 centerPos((centerRect.x + centerRect.z) / 2, (centerRect.y + centerRect.w) / 2);
	drawTextCenter(centerPos, textStr, color, textSize, shadow);
}

void ImGuiUtils::drawTextCenter4Y(Vec4 centerRect, std::string textStr, UIColor color, float textSize, bool shadow, float add)
{
	drawTextCenterY(Vec2(centerRect.x + add, (centerRect.y + centerRect.w) / 2), textStr, color, textSize, shadow, add);
}
void ImGuiUtils::drawBox(const AABB& blockAABB, UIColor color, UIColor lineColor, float lineWidth, bool fill, bool outline) {
	Vec3 lower = blockAABB.lower;
	Vec3 upper = blockAABB.upper;

	Vec3 diff = upper.sub(lower);
	Vec3 vertices[8];
	vertices[0] = Vec3(lower.x, lower.y, lower.z);
	vertices[1] = Vec3(lower.x + diff.x, lower.y, lower.z);
	vertices[2] = Vec3(lower.x, lower.y + diff.y, lower.z);
	vertices[3] = Vec3(lower.x + diff.x, lower.y + diff.y, lower.z);
	vertices[4] = Vec3(lower.x, lower.y, lower.z + diff.z);
	vertices[5] = Vec3(lower.x + diff.x, lower.y, lower.z + diff.z);
	vertices[6] = Vec3(lower.x, lower.y + diff.y, lower.z + diff.z);
	vertices[7] = Vec3(lower.x + diff.x, lower.y + diff.y, lower.z + diff.z);

	std::shared_ptr<glmatrixf> refdef = std::shared_ptr<glmatrixf>(Game.getClientInstance()->getrefdef()->correct());
	Vec3 origin = Game.getClientInstance()->getOrigin();
	Vec2 fov = Game.getClientInstance()->getFov();
	Vec2 screenSize = Game.getClientInstance()->guiData->realSize;

	if (fill) {
		// Convert the vertices to screen coordinates
		std::vector<Vec2> screenCords;
		for (int i = 0; i < 8; i++) {
			Vec2 screen;
			if (refdef->OWorldToScreen(origin, vertices[i], screen, fov, screenSize)) {
				screenCords.push_back(screen);
			}
		}

		// Return if there are less than four points to draw quads with
		if (screenCords.size() < 8) return;

		// Define the indices of the vertices to use for each quad face
		std::vector<std::tuple<int, int, int, int>> faces = {
			{0, 1, 3, 2},  // Bottom face
			{4, 5, 7, 6},  // Top face
			{0, 1, 5, 4},  // Front face
			{2, 3, 7, 6},  // Back face
			{1, 3, 7, 5},  // Right face
			{0, 2, 6, 4}   // Left face
		};

		// Draw the quads to fill the box
		for (auto face : faces) {
			drawlist->AddQuadFilled(screenCords[std::get<0>(face)].toImVec2(), screenCords[std::get<1>(face)].toImVec2(), screenCords[std::get<2>(face)].toImVec2(), screenCords[std::get<3>(face)].toImVec2(), color.toImColor());
			//drawlist->AddQuadFilled(screenCords[std::get<3>(face)].toImVec2(), screenCords[std::get<2>(face)].toImVec2(), screenCords[std::get<1>(face)].toImVec2(), screenCords[std::get<0>(face)].toImVec2(), color.toImColor());
		}
	}

	{
		// Convert the vertices to screen coordinates
		std::vector<std::tuple<int, Vec2>> screenCords;
		for (int i = 0; i < 8; i++) {
			Vec2 screen;
			if (refdef->OWorldToScreen(origin, vertices[i], screen, fov, screenSize)) {
				screenCords.emplace_back(outline ? (int)screenCords.size() : i, screen);
			}
		}

		// Return if there are less than two points to draw lines between
		if (screenCords.size() < 2) return;

		switch (outline) {
		case false: {
			// Draw lines between all pairs of vertices
			for (auto it = screenCords.begin(); it != screenCords.end(); it++) {
				auto from = *it;
				auto fromOrig = vertices[std::get<0>(from)];

				for (auto to : screenCords) {
					auto toOrig = vertices[std::get<0>(to)];

					// Determine if the line should be drawn based on the relative positions of the vertices
					bool shouldDraw = false;
					// X direction
					shouldDraw |= fromOrig.y == toOrig.y && fromOrig.z == toOrig.z && fromOrig.x < toOrig.x;
					// Y direction
					shouldDraw |= fromOrig.x == toOrig.x && fromOrig.z == toOrig.z && fromOrig.y < toOrig.y;
					// Z direction
					shouldDraw |= fromOrig.x == toOrig.x && fromOrig.y == toOrig.y && fromOrig.z < toOrig.z;

					if (shouldDraw) drawlist->AddLine(std::get<1>(from).toImVec2(), std::get<1>(to).toImVec2(), lineColor.toImColor(), lineWidth);
				}
			}
			return;
			break;
		}
		case true: {
			// Find start vertex
			auto it = screenCords.begin();
			std::tuple<int, Vec2> start = *it;
			it++;
			for (; it != screenCords.end(); it++) {
				auto cur = *it;
				if (std::get<1>(cur).x < std::get<1>(start).x) {
					start = cur;
				}
			}

			// Follow outer line
			std::vector<int> indices;

			auto current = start;
			indices.push_back(std::get<0>(current));
			Vec2 lastDir(0, -1);
			do {
				float smallestAngle = PI * 2;
				Vec2 smallestDir;
				std::tuple<int, Vec2> smallestE;
				auto lastDirAtan2 = atan2(lastDir.y, lastDir.x);
				for (auto cur : screenCords) {
					if (std::get<0>(current) == std::get<0>(cur))
						continue;

					// angle between vecs
					Vec2 dir = Vec2(std::get<1>(cur)).sub(std::get<1>(current));
					float angle = atan2(dir.y, dir.x) - lastDirAtan2;
					if (angle > PI) {
						angle -= 2 * PI;
					}
					else if (angle <= -PI) {
						angle += 2 * PI;
					}
					if (angle >= 0 && angle < smallestAngle) {
						smallestAngle = angle;
						smallestDir = dir;
						smallestE = cur;
					}
				}
				indices.push_back(std::get<0>(smallestE));
				lastDir = smallestDir;
				current = smallestE;
			} while (std::get<0>(current) != std::get<0>(start) && indices.size() < 8);

			// draw

			Vec2 lastVertex;
			bool hasLastVertex = false;
			for (auto& indice : indices) {
				Vec2 curVertex = std::get<1>(screenCords[indice]);
				if (!hasLastVertex) {
					hasLastVertex = true;
					lastVertex = curVertex;
					continue;
				}

				drawlist->AddLine(lastVertex.toImVec2(), curVertex.toImVec2(), lineColor.toImColor(), lineWidth);
				lastVertex = curVertex;
			}
			return;
			break;
		}
		}
	}
}

void ImGuiUtils::drawBox(const Vec3& blockPos, UIColor color, UIColor lineColor, float lineWidth, bool fill, bool outline) {
	AABB blockAABB;
	blockAABB.lower = blockPos;
	blockAABB.upper.x = blockPos.x + 1.f;
	blockAABB.upper.y = blockPos.y + 1.f;
	blockAABB.upper.z = blockPos.z + 1.f;
	ImGuiUtils::drawBox(blockAABB, color, lineColor, lineWidth, fill, outline);
}

bool ImGuiUtils::worldToScreen(const Vec3& pos, Vec2& out) {
	std::shared_ptr<glmatrixf> refdef = std::shared_ptr<glmatrixf>(Game.getClientInstance()->getrefdef()->correct());
	Vec3 origin = Game.getClientInstance()->getOrigin();
	Vec2 fov = Game.getClientInstance()->getFov();
	Vec2 screenSize = Game.getGuiData()->realSize;
	return refdef->OWorldToScreen(origin, pos, out, fov, screenSize);
}

inline bool WorldToScreen(Vec3 pos, Vec2& out)
{ // pos = pos 2 w2s, screen = output screen coords
	if (!Game.getGuiData()) {
		return false;
	}
	Vec2 displaySize = Game.getGuiData()->realSize;
	class LevelRenderer* lr = Game.getClientInstance()->getLevelRender();
	Vec3 origin = lr->getOrigin();
	Vec2 fov = Game.getClientInstance()->getFov();

	pos.x -= origin.x;
	pos.y -= origin.y;
	pos.z -= origin.z;

	auto GLMatrix = Game.getClientInstance()->getrefdef();
	std::shared_ptr<glmatrixf> matrix = std::shared_ptr<glmatrixf>(GLMatrix->correct());

	float x = matrix->transformx(pos);
	float y = matrix->transformy(pos);
	float z = matrix->transformz(pos);

	if (z > 0) return false;

	float mX = (float)displaySize.x / 2.0F;
	float mY = (float)displaySize.y / 2.0F;

	out.x = mX + (mX * x / -z * fov.x);
	out.y = mY - (mY * y / -z * fov.y);

	return true;
}