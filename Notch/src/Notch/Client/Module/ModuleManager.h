#pragma once

#include <type_traits>

#include "Modules/Module.h"

//Combat
#include "Modules/Combat/KillAura.h"
#include "Modules/Combat/Surround.h"
//Misc
//Render
#include "Modules/Render/PotionHud.h"
#include "Modules/Render/ViewModel.h"
#include "Modules/Render/NameTags.h"
#include "Modules/Render/Camera.h"
//Movement
#include "Modules/Movement/Velocity.h"
//Player
#include "Modules/Player/PacketMine.h"
#include "Modules/Player/AutoEmote.h"
//Client
#include "Modules/Client/CustomFont.h"
#include "Modules/Client/Debugconsole.h"
#include "Modules/Client/Test.h"
#include "Modules/Client/ClickGui.h"
#include "Modules/Client/Colors.h"
#include "Modules/Client/ArrayList.h"
//Unknow
class MinecraftUIRenderContext;
class ModuleManager {
private:
    std::vector<Module*> moduleList;
    bool initialized = false;
public:
    ~ModuleManager();
public:
    std::vector<Module*>* getModuleList() { return &this->moduleList; }
    const bool isInitialized() { return this->initialized; }
    void initModules();
    template <typename TRet>
    TRet* getModule() {
        if (!isInitialized())
            return nullptr;
        for (auto pMod : moduleList) {
            if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod)) {

                return pRet;
            }
        }
        return nullptr;
    };

    Module* getModuleByName(const std::string& moduleName) {
        std::string nameLower(moduleName);
        std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);

        for (Module* mod : moduleList) {
            std::string modNameLower = mod->getModuleName();
            std::transform(modNameLower.begin(), modNameLower.end(), modNameLower.begin(), ::tolower);
            if (strcmp(nameLower.c_str(), modNameLower.c_str()) == 0) return mod;
        }
        return nullptr;
    }
public:
    void onSaveConfig(json* currentConfig);
    void onLoadConfig(json* config);
    void onKeyUpdate(int key, bool isDown, bool& cancel);
    void onMouseClickUpdate(int mousekey, bool isDown, bool& cancel);
    void onWheelScroll(bool direction);
    void onImGuiRender(ImDrawList* drawlist);
    void onTick(LocalPlayer* actor);
    void onLevelRender();
    void onJoiningServer();
    void onRender(MinecraftUIRenderContext* c);
};


extern ModuleManager* moduleMgr;