#pragma once
#include <dxgi.h>
#include <dxgi1_4.h>
#include <d3d11.h>
#include <d3d12.h>
#include <d2d1_3.h>
#include "../Libraries/Libraries.h"
#include "../Utils/Logger.h"
#include "../Client/Module/ModuleManager.h"
#include "HookManager.h"

#include "../Libraries/Libs/Fonts/Mojangles.h"
#include "../Libraries/Libs/Fonts/ProductSansRegular.h"
#include "../Libraries/Libs/Fonts/ProductSansLight.h"
#include "../Libraries/Libs/Fonts/NotoSans.h"

#include "../GameData.h"
class DXHook {
public:

	static void Restore();

	static inline ID3D11Device* d3d11Device = nullptr;
	static inline ID3D12Device* d3d12Device = nullptr;
	static inline ID3D11DeviceContext* dContext = nullptr;
	static inline bool initImGui = false;
	typedef HRESULT(__thiscall* Present)(IDXGISwapChain3*, UINT, UINT);
	static inline Present oPresent;
	typedef HRESULT(__thiscall* ResizeBuffers)(IDXGISwapChain*, int, int, int, DXGI_FORMAT, int);
	static inline ResizeBuffers oResizeBuffers;
	static void onImGuiRender(ImDrawList*);

	//static void onImGuiRender(ImDrawList* d);
	static HRESULT presentCallback(IDXGISwapChain3* pSwapChain, UINT syncInterval, UINT flags);
	static HRESULT resizeBuffersHook(IDXGISwapChain* ppSwapChain, int bufferCount, int width, int height, DXGI_FORMAT newFormat, int swapChainFlags);
};