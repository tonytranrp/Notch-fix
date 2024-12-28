#pragma once
#include "Libs/minhook/minhook.h"

#if defined _M_X64
#pragma comment(lib, "MinHook-x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "MinHook-x86.lib")
#endif

#include "Libs/xorstr.hpp"

#include "Libs/ImGui/imgui.h"
#include "Libs/ImGui/imgui_internal.h"
#include "Libs/ImGui/imgui_impl_win32.h"
#include "Libs/ImGui/imgui_impl_dx11.h"
#include "Libs/ImGui/imgui_impl_dx12.h"

#include "Libs/ImFX/imfx.h"

#include "Libs/Kiero/kiero.h"

#include "Libs/Json.hpp"

#include "Libs/entt/entt/entt.hpp"