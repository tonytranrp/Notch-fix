#pragma once
class ActorRenderDispatcher__renderHook : public Hook {
public:
	static inline void* detour;
	static void renderDetour(void* _this, void* entityRenderContext, Actor* entity, const Vec3* cameraTargetPos, const Vec3* pos, const Vec2* rot, bool ignoreLighting) {
		//for (int i = 0; i <= 15; i++)
			Memory::CallFunc<void, void*, void*, Actor*, const Vec3*, const Vec3*, const Vec2*, bool>(detour, _this, entityRenderContext, entity, cameraTargetPos, pos/*&pos->add(i)*/, rot, ignoreLighting);
	}
	virtual void Initialize() override {
		Memory::CreateHook(getSig("ActorRenderDispatcher::render"), (void*)&renderDetour, &detour, "ActorRenderDispatcher::render Hook");
	}
};