#include "PacketMine.h"

PacketMine::PacketMine() : Module("PacketMine", "Automatically mine selected blocks", Category::PLAYER, 0x0) {
	addSlider<float>("Range", "Range to mineable", &range, 0.f, 9.f);
	addSlider<float>("Mine Speed", "Increase mining speed", &minespeed, 0.5f, 2.5f);
	addBoolCheck("Silent", "Auto switch to the best pickaxe in hotbar with silent", &silent);
};

void PacketMine::setBreakPos(const Vec3i& blockPos, uint8_t face) {
};
void PacketMine::ResetAllFlag() {
};
void PacketMine::onSendPacket(Packet* pkt, bool& shouldCancel) {
};
void PacketMine::onTick(LocalPlayer* lp) {
};
void PacketMine::onRender(MinecraftUIRenderContext* ctx) {
};
void PacketMine::onImGuiRender(ImDrawList* drawlist) {
};