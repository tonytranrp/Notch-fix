#pragma once
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
class Logger {
public:
	std::string getTime() {
		auto now = std::chrono::system_clock::now();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
		std::tm tm_now;
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		localtime_s(&tm_now, &now_time);

		std::ostringstream oss;
		oss << std::put_time(&tm_now, xorstr_("%Y-%m-%d %H:%M:%S"))
			<< xorstr_(".") << std::setw(3) << std::setfill('0') << millis % 1000;
		return oss.str();
	}

	std::string changeConsoleColor(int colorCode) {
		return xorstr_("\033[1;") + std::to_string((colorCode ? colorCode : -30) + 30) + xorstr_("m");
	}

	std::string GetColorByStatus(const std::string& status) {
		static const std::unordered_map<std::string, int> statusColorMap = {
			{xorstr_("WAIT"), 3}, {xorstr_("FAIL"), 1}, {xorstr_("NULLPTR"), 1},
			{xorstr_("NOT NULLPTR"), 2}, {xorstr_("ERROR"), 1}, {xorstr_("OKAY"), 2},
			{xorstr_("INFO"), 2}, {xorstr_("SUCCESS"), 2}
		};
		auto it = statusColorMap.find(status);
		return changeConsoleColor(it != statusColorMap.end() ? it->second : 0);
	}

	void logging(const std::string& text, const std::string& status) {
		std::cout << changeConsoleColor(0) + xorstr_("[") + changeConsoleColor(4) + getTime()
			+ changeConsoleColor(1) + xorstr_("-") + changeConsoleColor(6) + xorstr_("Notch")
			+ changeConsoleColor(1) + xorstr_(" | ") + changeConsoleColor(6) + xorstr_("0.0.1")
			+ changeConsoleColor(0) + xorstr_("] [ ") + GetColorByStatus(status) + status
			+ changeConsoleColor(0) + xorstr_(" ]   ") + text << std::endl;
	}
};

#define logF(text, status) { Logger logger; logger.logging(text, status); }