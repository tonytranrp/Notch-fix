#include "Debugconsole.h"

DebugConsole g_DebugConsole;
UIColor colors[] = {
    UIColor(0, 0, 0),       // BLACK       30
        UIColor(197, 15, 31),   // RED         31
        UIColor(19, 161, 14),   // GREEN       32
        UIColor(193, 156, 0),   // YELLOW      33
        UIColor(0, 55, 218),    // BLUE        34
        UIColor(136, 23, 152),  // MAGENTA     35
        UIColor(58, 150, 221),  // CYAN        36
        UIColor(204, 204, 204), // WHITE       37
};
std::unordered_map<std::string, UIColor> colorMap = {
            {"WAIT", colors[3]}, {"FAIL", colors[1]},
            {"NULLPTR", colors[1]}, {"ERROR", colors[1]},
            {"OKAY", colors[2]}, {"NOT NULLPTR", colors[2]},
            {"INFO", colors[2]}, {"SUCCESS", colors[2]}
};
DebugConsole::DebugConsole() : Module("DebugConsole", "A GUI used to display logs and accept user input.", Category::CLIENT, VK_TAB) {
}

Vec4 input_rect;
bool input_status = false;
void DebugConsole::onMouseClickUpdate(int mouseKey, bool isDown, bool& cancel) {
    if (mouseKey == 1) {
        isLeftClickDown = isDown;
        isHoldingLeftClick = isDown;
    }
    else if (mouseKey == 2) {
        isRightClickDown = isDown;
        isHoldingRightClick = isDown;
    }
};

void DebugConsole::onWheelScroll(bool direction) {
    if (!direction) scrolldir++;
    else scrolldir--;
};

void DebugConsole::render(ImDrawList* drawlist) {
    if (!isEnabled()) return;

    ImGuiIO& io = ImGui::GetIO();
    const float padding = 10.0f;
    const float console_width = io.DisplaySize.x * 0.5f;
    const float console_height = io.DisplaySize.y * 0.5f;
    const Vec2 console_pos(io.DisplaySize.x * 0.25f, io.DisplaySize.y * 0.25f);

    // Console background
    Vec4 console_rect(console_pos.x, console_pos.y, console_pos.x + console_width, console_pos.y + console_height);
    ImGuiUtils::fillRectangle(console_rect, UIColor(0, 0, 0, 200));
    ImGuiUtils::drawRectangle(console_rect, UIColor(255, 255, 255, 100), 1.0f);

    // Render console log with scrolling support
    const float log_height = ImGuiUtils::getTextHeight(1.0f) + 2.0f;
    float visible_lines = (console_height - padding * 2) / log_height - (log_height + log_height + 2);
    float max_scroll = console_log.size() - console_log.size() + 1;

    if (scrolldir < 0) scrolldir = 0;  // Prevent scrolling beyond the top
    if (scrolldir > max_scroll) scrolldir = max_scroll;  // Prevent scrolling beyond the bottom

    float y_offset = console_pos.y + padding - scrolldir * log_height;
    for (int i = 0; i < console_log.size(); i++) {
        LogMessage log = console_log[i];
        if (y_offset + log_height > console_pos.y && y_offset < console_pos.y + console_height) {  // Only render visible logs
            ImGuiUtils::drawText(Vec2(console_pos.x + padding, y_offset), log.time, UIColor(150, 150, 150, 255), 1.0f);
            auto it = colorMap.find(log.status);
            UIColor color = (it != colorMap.end()) ? it->second : UIColor(0, 0, 0);
            ImGuiUtils::drawText(Vec2(console_pos.x + padding + ImGuiUtils::getTextWidth(log.time + " ", 1.0f), y_offset), log.message, UIColor(color.r, color.g, color.b, 255), 1.0f);
        }
        y_offset += log_height;
    }
    // Input box
    input_rect = Vec4(console_pos.x + padding, console_pos.y + console_height - ImGuiUtils::getTextHeight(1.0f) - padding * 2,
        console_pos.x + console_width - padding, console_pos.y + console_height - padding);
    ImGuiUtils::fillRectangle(input_rect, UIColor(50, 50, 50, 200));
    ImGuiUtils::drawRectangle(input_rect, UIColor(255, 255, 255, 200));
    ImGuiUtils::drawText(Vec2(input_rect.x + 5, input_rect.y + 2), input_buffer, UIColor(255, 255, 255, 255), 1.0f);
    Vec2 mousePos = Game.getClientInstance()->getMousePos();
    if (input_rect.contains(&mousePos) && isLeftClickDown) {
        if (input_status) input_status = false;
        else if (!input_status) input_status = true;
        isLeftClickDown = false;
    }


    // Cursor blink
    if (input_status) {
        static float barOpacity = 1.f;
        static bool up = false;
        if (!up) {
            barOpacity -= io.DeltaTime * 2.f;
            if (barOpacity < 0.f) {
                barOpacity = 0.f;
                up = true;
            }
        }
        else {
            barOpacity += io.DeltaTime * 2.f;
            if (barOpacity > 1.f) {
                barOpacity = 1.f;
                up = false;
            }
        }
        float cursor_x = input_rect.x + 5 + ImGuiUtils::getTextWidth(input_buffer, 1.0f);
        Vec4 cursor_rect(cursor_x, input_rect.y + 2, cursor_x + 2, input_rect.w - 2);
        ImGuiUtils::fillRectangle(cursor_rect, UIColor(255, 255, 255, barOpacity * 255));
    }
}

void DebugConsole::onKey(int key, bool isDown, bool& cancel) {
    if (isEnabled() && !isDown) return;
    if (input_status) {
        cancel = true;
        if (key == VK_RETURN) {
            if (!input_buffer.empty()) {
                processCommand(input_buffer);
                input_buffer.clear();
            }
        }
        else if (key == VK_BACK) {
            if (!input_buffer.empty()) {
                input_buffer.pop_back();
            }
        }
        else if (key >= 32 && key <= 126) { // Printable ASCII characters
            input_buffer += (char)key;
        }
    };
}

std::string DebugConsole::getTime() {
    auto now = std::chrono::system_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::tm tm_now;
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    localtime_s(&tm_now, &now_time);

    std::ostringstream oss;
    oss << std::put_time(&tm_now, xorstr_("%H:%M:%S"));
    return oss.str();
}


void DebugConsole::processCommand(const std::string& command) {
}

void DebugConsole::addLog(LogMessage log) {
    console_log.push_back(log);
};

void DebugConsole::addLog(std::string msg, std::string status) {
    LogMessage LogMessagStruct;
    LogMessagStruct.message = msg;
    LogMessagStruct.status = status;
    LogMessagStruct.time = getTime();
    addLog(LogMessagStruct);
};