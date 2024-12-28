#pragma once

#include "SDK/ClientInstance/ClientInstance.h"
#include "SDK/Actor/Actor.h"
#include "run.h"

class GameData {
public:
    int fps = 0;
    Vec2 mousepos;
    ClientInstance* clientinstance = nullptr;

    ClientInstance* getClientInstance() {
        return clientinstance;
    };
    bool canUseMoveKeys() {
        CURSORINFO cursorInfo = CURSORINFO();
        cursorInfo.cbSize = sizeof(CURSORINFO);

        if (GetCursorInfo(&cursorInfo))
            return (cursorInfo.flags & 0x00000001) == 0;

        return true;
    }
    LocalPlayer* getLocalPlayer() {
        if (clientinstance != nullptr)
            return clientinstance->getLocalPlayer();
        return nullptr;
    };

    GuiData* getGuiData() {
        if (clientinstance != nullptr)
            return clientinstance->guiData;
        return nullptr;
    };

    void uninject() {
        Run::running = false;
    };
};

extern GameData Game;