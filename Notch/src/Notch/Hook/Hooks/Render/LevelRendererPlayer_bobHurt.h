#pragma once
#pragma once
#include "../BaseHook.h"
#include "../../../Utils/Memory.h"
#include "../../../GameData.h"
#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/Manager.h"

#include <glm/glm/ext/matrix_clip_space.hpp>
#include <glm/glm/ext/matrix_relational.hpp>
#include <glm/glm/ext/matrix_transform.hpp>
#include <glm/glm/gtc/constants.hpp>
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/trigonometric.hpp>
class LevelRendererPlayer__bobHurtHook : public Hook {
public:
	static inline void* LevelRendererPlayerbobHurt;
	static __int64 LevelRendererPlayerbobHurtCallback(__int64 _this, glm::mat4* matrix) {
		auto ret = Memory::CallFunc<__int64, __int64, glm::mat4*>(LevelRendererPlayerbobHurt, _this, matrix);
		auto& mat = *matrix;
		if (moduleMgr->isInitialized()) {
			static ViewModel* vMod = moduleMgr->getModule<ViewModel>();
			if (vMod->isEnabled()) {
				;
				if (vMod->translate) mat = glm::translate<float>(mat, glm::vec3(vMod->translateVec.x, vMod->translateVec.y, vMod->translateVec.z));
				if (vMod->scale) mat = glm::scale<float>(mat, glm::vec3(vMod->scaleVec.x - vMod->mainHand, vMod->scaleVec.y, vMod->scaleVec.z));
				if (vMod->rotate) mat = glm::rotate<float>(mat, vMod->rotAngle, glm::vec3(vMod->rotateVec.x, vMod->rotateVec.y, vMod->rotateVec.z));
			}
		};
		return ret;
	};
	virtual void Initialize() override {
		Memory::CreateHook(getSig("LevelRendererPlayer::bobHurt"), &LevelRendererPlayerbobHurtCallback, &LevelRendererPlayerbobHurt, "LevelRendererPlayer::bobHurt Hook");
	}
};