#pragma once
#include "../Module.h"
#include "../../../../SDK/Packet/BasePacket.h"
#include "../../../../SDK/Block/Block.h"

class PacketMine : public Module {
private:
	float range = 6.f;
	float minespeed = 1.15f;
	bool silent = true;
	Vec3i breakPos{ 0,0,0 };
	uint8_t face = -1;

	std::pair<int, float> getbestSlot(Block* block);
public:
	bool mineFlag = false;
	PacketMine();
	void setBreakPos(const Vec3i& bPos, uint8_t f);
	void ResetAllFlag();

	virtual void onSendPacket(Packet* packet, bool& shouldCancel);
	virtual void onTick(LocalPlayer* lp) override;
	virtual void onRender(MinecraftUIRenderContext* ctx) override;
	virtual void onImGuiRender(ImDrawList* drawlist) override;
};