#pragma once
#include <vector>
#include <string>
#include "../../../../Utils/ImGuiUtils.h"
#include "../Module.h"
#include "../../ModuleManager.h"
#include "../../../Config/ConfigManager.h"
#include "../../../../Libraries/Libs/ImFX/imfx.h"

#include "../../../../GameData.h"
#include "../../../../Utils/Input.h"
extern UIColor colors[];
extern std::unordered_map<std::string, UIColor> colorMap;

struct LogMessage {
public:
    std::string time; /*Example: 00:00*/
    std::string status; /*Example: INFO*/ /*
        Can use: 
			WAIT // YELLOW
            FAIL // RED
            NULLPTR // RED
            ERROR // RED
            NOT NULLPTR // GREEN
            OKAY // GREEN
			INFO // GREEN
            SUCCESS // GREEN
        */
    std::string message; /*Example: Test*/
};
class DebugConsole : public Module {
private:
    bool isLeftClickDown = false;
    bool isRightClickDown = false;
    bool isHoldingLeftClick = false;
    bool isHoldingRightClick = false;

    std::vector<LogMessage> console_log;
    std::string input_buffer;
    int scrolldir = 0;
public:
    DebugConsole();

    void render(ImDrawList* drawlist);
    virtual void onKey(int key, bool isDown, bool& cancel) override;
    virtual void onMouseClickUpdate(int mouseKey, bool isDown, bool& cancel) override;
    virtual void onWheelScroll(bool direction) override;
    std::string getTime();
    void processCommand(const std::string& command);
    void addLog(LogMessage logstruct);
    void addLog(std::string msg, std::string status="INFO");
};
// global_instance
extern DebugConsole g_DebugConsole;