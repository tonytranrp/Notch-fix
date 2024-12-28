#include "HookManager.h"
// Hook include
#include "Hooks/Render/Font_drawTransformed.h"
#include "Hooks/Render/LevelRendererPlayer_bobHurt.h"
#include "Hooks/Render/LevelRendererPlayer_getFov.h"
#include "Hooks/Render/CameraAvoidanceSystemUtil_calculateHardDistanceConstraint.h"
#include "Hooks/Render/ScreenView_SetupAndRender.h"
#include "Hooks/Render/ActorRenderDispatcher_render.h"
#include "Hooks/Render/Options_getGamma.h"
#include "Hooks/Render/HudMobEffectRenderer_render.h"
#include "Hooks/Render/LevelRenderer_renderLevel.h"
#include "Hooks/Render/UIScene_render.h"
#include "Hooks/Network/ConnectionRequest_create.h"
#include "Hooks/Device/keyboard_feed.h"
#include "Hooks/Device/MouseDevice_feed.h"
#include "Hooks/Misc/ClientInstance_update.h"
#include "Hooks/Packet/LoopbackPacketSender_SendToServer.h"
#include "Hooks/Actor/GameMode_startDestroyBlock.h"
#include "Hooks/Actor/Actor_lerp.h"
#include "Hooks/Actor/Level_tick.h"
// End
bool HookManager::initalize = false;

void HookManager::init() {
	Hooks.push_back(new ClientInstance__updateHook());
	Hooks.push_back(new Keyboard__feedHook());
	Hooks.push_back(new MouseDevice__feedHook());
	Hooks.push_back(new Font__drawTransformedHook());
	Hooks.push_back(new LoopbackPacketSender__SendToServerHook());
	Hooks.push_back(new LevelRendererPlayer__bobHurtHook());
	Hooks.push_back(new LevelRendererPlayer__getFovHook());
	Hooks.push_back(new LevelRenderer__renderLevelHook());
	Hooks.push_back(new UIScene__renderHook());
	Hooks.push_back(new ConnectionRequest__createHook());
	Hooks.push_back(new CameraAvoidanceSystemUtil__calculateHardDistanceConstraintHook());
	Hooks.push_back(new ScreenView__SetupAndRenderHook());
	Hooks.push_back(new HudMobEffectRenderer__renderHook());
	Hooks.push_back(new ActorRenderDispatcher__renderHook());
	Hooks.push_back(new Options__getGammaHook());
	Hooks.push_back(new GameMode__startDestroyBlockHook());
	Hooks.push_back(new Actor__lerpHook());
	Hooks.push_back(new Level__tickHook());
	for (Hook* hook : Hooks) {
		hook->Initialize();
	}

	initalize = true;
};

Hook* HookManager::getHook(Hook* other) {
	while (!initalize) Sleep(100);

	for (Hook* hook : Hooks) {
		if (hook == other) return hook;
	}
}