#include "NameTags.h"
NameTags::NameTags() : Module("NameTags", "Displays peoples names through walls", Category::RENDER, 0x0) {
	addBoolCheck("Self", "Shows your nametag for you while in 3rd person mode.", &ThirdPersonNameTag);
};

void NameTags::onImGuiRender(ImDrawList* d) {
	auto plr = Game.getLocalPlayer();
	if (!d || !plr) return;

	//entityList = plr->getLevel()->getRuntimeActorList();
 //   for (Actor* actor : entityList) {
	//	logF(StringUtil::combine("ActorNameTag: ", actor->getNameTag()), "INFO");
 //   }
};
bool patched = false;
void NameTags::onTick(LocalPlayer* actor) {
    if (!ThirdPersonNameTag || !actor) return;
    instructionPointer = getSig("ThirdPersonNameTag");

    if (instructionPointer && !patched) {
        memcpy(originalBytes, instructionPointer, instructionSize);

        DWORD protect;
        VirtualProtect(instructionPointer, instructionSize, PAGE_EXECUTE_READWRITE, &protect);
        memset(instructionPointer, 0x90 /*No-Operation*/, instructionSize);
        VirtualProtect(instructionPointer, instructionSize, protect, &protect);
        patched = true;
    }
}

void NameTags::onDisable() {
    if (!ThirdPersonNameTag && !patched) return;

    if (instructionPointer) {
        DWORD protect;
        VirtualProtect(instructionPointer, instructionSize, PAGE_EXECUTE_READWRITE, &protect);
        memcpy(instructionPointer, originalBytes, instructionSize);
        VirtualProtect(instructionPointer, instructionSize, protect, &protect); 
        patched = false;
    }
}