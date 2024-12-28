#pragma once

#include <Windows.h>
#include <thread>
#include <fstream>
#include <wininet.h>
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "wininet.lib")
#include "../../Libraries/Libraries.h"

class Network {
public:
    static void downloadFile(const std::string& name, const std::string& url, const std::string& path);
};