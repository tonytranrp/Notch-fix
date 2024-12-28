#include "Notch.h"

bool Initialized;
bool& MH_Initialized() {
    return Initialized;
}
void log(std::string msg, std::string titl) {
    logF(msg, titl);
    g_DebugConsole.addLog(msg, titl);
};
DWORD APIENTRY Notch::ejectThread(HMODULE lpParam) {
    while (Run::running) {
        Sleep(10);
    }
    std::lock_guard<std::mutex> lock(mutex);
    MH_Uninitialize();
    HookManager::RestoreImGui();
    ImFX::CleanupFX();
    if (MH_Initialized())
        MH_Uninitialize();

    HookManager::RestoreImGui();
    ImFX::CleanupFX();

    if (configMgr) {
        configMgr->saveConfig();
        delete configMgr;
        configMgr = nullptr;
    }

    if (moduleMgr) {
        delete moduleMgr;
        moduleMgr = nullptr;
    }

    if (cmdMgr) {
        delete cmdMgr;
        cmdMgr = nullptr;
    }

    if (prefixMgr) {
        delete prefixMgr;
        prefixMgr = nullptr;
    }
    if (Run::closeConsole) Notch::closeConsole();
    AudioSystem::getInstance().play(xorstr_("Audios\\uninject.wav"));
    winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, []() {
        winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(L"");
        });

#if _DEBUG
#else
    if (Game.getLocalPlayer() != nullptr) Game.getLocalPlayer()->displayClientMessage("%sEjected!", RED);
#endif
    Sleep(200);
    FreeLibraryAndExitThread(lpParam, 0);
 };
void Notch::initialize() {
    init();
    InjectTime = TimeUtil::getCurrentMs();
    FileSystem::Initalize();
    Notch::openConsole();

    std::string ver = version::GET_VERSION();
    log(StringUtil::combine("MC Version ", ver), "INFO");

    bool supported = Manager::checkVer(version::supportedVersion);
    if (!supported) {
        log("This Minecraft version is not supported", "FAIL");
        log(StringUtil::combine("Supported Version: ", StringUtil::join(version::supportedVersion, ", ")), "INFO");
        Run::closeConsole = false;
        Run::running = false;
    }
    else if (supported) {
        Manager::init();
        AudioSystem::getInstance().play(xorstr_("Audios\\inject.wav"));
        log(xorstr_("Initializing Hooks"), xorstr_("WAIT"));
       
        if (MH_Initialize() == MH_OK) {
            MH_Initialized() = true;
            HookManager::initImGui();
            HookManager::init();
        }
        log(xorstr_("ClientInstance"), Game.getClientInstance() == nullptr ? xorstr_("NULLPTR") : xorstr_("NOT NULLPTR"));
       
        if (Game.getClientInstance() != nullptr)
            log(xorstr_("GuiData"), Game.getGuiData() == nullptr ? xorstr_("NULLPTR") : xorstr_("NOT NULLPTR"));
         
        winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, []() {
            winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(L"Notch");
            });
        log(StringUtil::combine("ClientInstance Found at: ", Game.getClientInstance()->VTable), "INFO");

        Sleep(10);
        log("Initializing modules.", "WAIT");
        moduleMgr->initModules();
        log("Initialized Modules", "OKAY");
        configMgr->loadConfig("default");
        log("Initializing Commands.", "WAIT");
        cmdMgr->initCommands();
        log("Initialized Commands", "OKAY");
        log("Initialized Client", "OKAY");
#if _DEBUG
#else
        static LocalPlayer* lp = Game.getLocalPlayer();
        static GuiData* gu = Game.getGuiData();
        if (lp != nullptr) {
            log("LocalPlayer", "NOT NULLPTR");
            if (lp->getLevel()) log("LP -> Level", "NOT NULLPTR");
            else log("LP -> Level", "NULLPTR");
            lp->displayClientMessage("%sInjected!", GREEN);
            lp->displayClientMessage("NameTag: %s%s", YELLOW, lp->getNameTag());
            Vec3 Pos = lp->getPosition();
            lp->displayClientMessage("XYZ: %i, %i, %i", (int)Pos.x, (int)Pos.y, (int)Pos.z);
            if (gu != nullptr)
                lp->displayClientMessage("WindowSizeReal: %i, %i", (int)Game.getGuiData()->realSize.x, (int)Game.getGuiData()->realSize.y);
        }
        else
            log("LocalPlayer", "NULLPTR");
#endif
    }
};

Vec2 ClientInstance::getMousePos() {
    return Game.mousepos;
};