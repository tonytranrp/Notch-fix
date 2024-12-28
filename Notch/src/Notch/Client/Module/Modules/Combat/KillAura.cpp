#include "KillAura.h"

KillAura::KillAura() : Module("KillAura", "Attacks entities around you automatically.", Category::COMBAT, 0x0) {
	addSlider<float>("Range", "Range of Target.", &range, 0.1f, 15.f);
	addBoolCheck("Swing", "Swing on attack", &swing);
	addEnumSetting("Target", "enum of target list", { "Single", "Multi" }, &target);
}

void KillAura::findEntity() {
	LocalPlayer* lp = Game.getLocalPlayer();
	if (!lp) return;
	Level* level = lp->getLevel();

	std::vector<Actor*> temp = level->getRuntimeActorList();
	//lp->jumpFromGround();

	for (Actor* actor : temp) {
		if (!actor->isPlayer() || actor->isLocalPlayer()) continue;
		if (actor->getPosition().dist(lp->getPosition()) < range)
			entityList.push_back(actor);
	}
}

void KillAura::onTick(LocalPlayer* actor) {
	entityList.clear();
	if (!actor) return;
	findEntity();
	
	GameMode* gm = actor->getGameMode();
	if (entityList.empty()) return;
	for (Actor* ent : entityList) {
		gm->attack(*ent);
		if (swing)
			actor->swing();
		if (target == 0) break;
	}
}

void KillAura::onImGuiRender(ImDrawList* d) {
	if (!d) return;

}