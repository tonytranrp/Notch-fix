#include "DXHook.h"

void DXHook::Restore() {
    MH_DisableHook(MH_ALL_HOOKS);
    Sleep(10);
}
void DXHook::onImGuiRender(ImDrawList* drawlist) {
    ImGuiUtils::setDrawList(drawlist);

    ImGuiIO& io = ImGui::GetIO();
    if (!moduleMgr->isInitialized())
        return;
    static CustomFont* cFontMod = moduleMgr->getModule<CustomFont>();

    switch (cFontMod->fontType) {
    case 0: { // Mojangles
        io.FontDefault = io.Fonts->Fonts[0];
        ImGuiUtils::setFontSize(22.f);
        ImGuiUtils::setShadowOffset(2.f);
        break;
    }
    case 1: { // ProductSans
        io.FontDefault = io.Fonts->Fonts[1];
        ImGuiUtils::setFontSize(25.f);
        ImGuiUtils::setShadowOffset(1.f);
        break;
    }
    case 2: { // ProductSansLight
        io.FontDefault = io.Fonts->Fonts[2];
        ImGuiUtils::setFontSize(25.f);
        ImGuiUtils::setShadowOffset(1.f);
        break;
    }
    case 3: { // NotoSans
        io.FontDefault = io.Fonts->Fonts[3];
        ImGuiUtils::setFontSize(25.f);
        ImGuiUtils::setShadowOffset(2.f);
        break;
    }
    }

    moduleMgr->onImGuiRender(drawlist);
    static ClickGui* clickGuiMod = moduleMgr->getModule<ClickGui>();
    clickGuiMod->render(drawlist);
    static DebugConsole* debugMod = moduleMgr->getModule<DebugConsole>();
    debugMod->render(drawlist);
}

HRESULT DXHook::presentCallback(IDXGISwapChain3* pSwapChain, UINT syncInterval, UINT flags) {
    if (Game.getClientInstance() == nullptr || Game.getGuiData() == nullptr)
        return oPresent(pSwapChain, syncInterval, flags);

    HWND window = (HWND)FindWindowA(nullptr, (LPCSTR)"Minecraft");

    if (SUCCEEDED(pSwapChain->GetDevice(IID_PPV_ARGS(&d3d11Device)))) {
        ID3D11Texture2D* pBackBuffer = nullptr;
        IDXGISurface* dxgiBackBuffer = nullptr;
        ID3D11RenderTargetView* mainRenderTargetView = nullptr;

        d3d11Device->GetImmediateContext(&dContext);
        pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        pSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));
        d3d11Device->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);

        if (!initImGui) {
            if (ImGui::GetCurrentContext() == nullptr) {
                ImGui::CreateContext();
            }

            ImGuiIO& io = ImGui::GetIO();
            ImGui::StyleColorsDark();
            io.Fonts->AddFontFromMemoryTTF((void*)Mojangles, sizeof(Mojangles), 200.f); // 200.f
            io.Fonts->AddFontFromMemoryTTF((void*)ProductSansRegular, sizeof(ProductSansRegular), 100.f); // 100.f
            io.Fonts->AddFontFromMemoryTTF((void*)ProductSansLight, sizeof(ProductSansLight), 100.f); // 100.f
            io.Fonts->AddFontFromMemoryTTF((void*)NotoSans, sizeof(NotoSans), 100.f); // 100.f
            io.IniFilename = NULL;

            ImGui_ImplWin32_Init(window);
            ImGui_ImplDX11_Init(d3d11Device, dContext);
            initImGui = true;
        }
        if (Game.getGuiData() == nullptr) return oPresent(pSwapChain, syncInterval, flags);
        ImFX::NewFrame(d3d11Device, dxgiBackBuffer, GetDpiForWindow(window));
        pBackBuffer->Release();
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame(ImVec2(Game.getGuiData()->realSize.x, Game.getGuiData()->realSize.y));

        ImGui::NewFrame();
        onImGuiRender(ImGui::GetBackgroundDrawList());
        ImGui::EndFrame();
        ImGui::Render();

        dContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
        ImDrawData* drawData = ImGui::GetDrawData();
        ImGui_ImplDX11_RenderDrawData(drawData);
        ImFX::EndFrame();

        dContext->Flush();
        dContext->Release();
        if (mainRenderTargetView) mainRenderTargetView->Release();
        d3d11Device->Release();
    }
    else if (SUCCEEDED(pSwapChain->GetDevice(IID_PPV_ARGS(&d3d12Device)))) {
        static_cast<ID3D12Device5*>(d3d12Device)->RemoveDevice();
    }

    return oPresent(pSwapChain, syncInterval, flags);
}

HRESULT DXHook::resizeBuffersHook(IDXGISwapChain* ppSwapChain, int bufferCount, int width, int height, DXGI_FORMAT newFormat, int swapChainFlags) {
    ImFX::CleanupFX();
    return oResizeBuffers(ppSwapChain, bufferCount, width, height, newFormat, swapChainFlags);
}

void HookManager::initImGui() {
    bool isDx11 = false;
    if (kiero::init(kiero::RenderType::D3D12) != kiero::Status::Success) {
        if (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success) {
            logF("Failed to initialize kiero!", "FAIL");
            return;
        }
        isDx11 = true;
    }

    if (!isDx11) {
        if (kiero::bind(145, (void**)&DXHook::oResizeBuffers, DXHook::resizeBuffersHook) != kiero::Status::Success) {
            logF("Failed to hook Resize Buffers Hook!", "FAIL");
            return;
        }
        //logF("Successfully hooked Resize Buffers Hook!", "OKAY");
        if (kiero::bind(140, (void**)&DXHook::oPresent, DXHook::presentCallback) != kiero::Status::Success) {
            logF("Failed to hook Present D3D12 Hook!", "FAIL");
            return;
        }
        //logF("Successfully hooked Present D3D12 Hook!", "OKAY");
    }
    else {
        if (kiero::bind(13, (void**)&DXHook::oResizeBuffers, DXHook::resizeBuffersHook) != kiero::Status::Success) {
            logF("Failed to hook Resize Buffers Hook!", "FAIL");
            return;
        }
        //logF("Successfully hooked Resize Buffers Hook!", "OKAY");
        if (kiero::bind(8, (void**)&DXHook::oPresent, DXHook::presentCallback) != kiero::Status::Success) {
            logF("Failed to hook Present D3D11 Hook!", "FAIL");
            return;
        }
        //logF("Successfully hooked Present D3D11 Hook!", "OKAY");
    }
    logF("ImGui enabled", "OKAY");
}

void HookManager::RestoreImGui() {
    DXHook::Restore();
}