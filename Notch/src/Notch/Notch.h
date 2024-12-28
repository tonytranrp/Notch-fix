#pragma once
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.UI.Core.h>
#include <functional>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>
#include <cstdarg>
#include <string>
#include <bitset>
#include <vector>
#include <chrono>
#include <thread>
#include <array>
#include <mutex>
#include <map>

#pragma comment(lib, "version.lib")

#include <dxgi.h>
#include <dxgi1_4.h>
#include <d3d11.h>
#include <d3d12.h>
#include <d2d1_3.h>

#include "Libraries/Libraries.h"
#include "Utils/HMath.h"

#include "Client/System/AudioSystem.h"
#include "Client/System/FileSystem.h"
#include "Client/System/Network.h"

#include "Client/Module/Modules/Client/Debugconsole.h"
#include "Client/Module/ModuleManager.h"
#include "Client/Command/CommandManager.h"
#include "Client/Command/Prefix.h"
#include "Client/Config/ConfigManager.h"

#include "Utils/TimeUtil.h"
#include "Utils/StringUtil.h"
#include "Utils/Memory.h"
#include "Utils/Logger.h"
#include "Utils/TextFormat.h"

#include "Hook/HookManager.h"

#include "SDK/Render/HashedString.h"
#include "SDK/Packet/Packet.h"
#include "SDK/Actor/EntityContext.h"
#include "SDK/Actor/Actor.h"
#include "SDK/ClientInstance/ClientInstance.h"
#include "SDK/ClientInstance/GuiData.h"
#include "SDK/ClientInstance/LoopbackPacketSender.h"

#include "GameData.h"

#include "run.h"
#include "version.h"

class Notch {
private:
    static inline std::mutex mutex;
public:
    static inline bool Initialized;
    static inline bool ShouldUIRender = true;
    static inline uint64_t InjectTime;
    static void initialize();
    static DWORD APIENTRY ejectThread(HMODULE lpParam);
    static void openConsole() {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        AllocConsole();
        SetConsoleTitleA(xorstr_("NotchHack"));
        FILE* out;
        freopen_s(&out, xorstr_("CONOUT$"), xorstr_("w"), stdout);
        freopen_s(&out, xorstr_("CONIN$"), xorstr_("r"), stdin);
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        Sleep(10);
        MH_Uninitialize();
        system("cls");
    };
    static void closeConsole() {
        system("cls");
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        FreeConsole();
    };
};

extern void log(std::string msg, std::string titl);