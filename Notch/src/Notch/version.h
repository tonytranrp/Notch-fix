#pragma once
#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>
#include <cstdarg>
#include <psapi.h>
#include <string>
#include <vector>
#include <set>

class version {
public:
    static std::string GET_VERSION(bool patchVersion = true);
    static inline std::set<std::string> supportedVersion = {
        "1.21.0.3",
        "1.21.2.2",
        "1.21.20.3",
        "1.21.21.1",
        "1.21.22.1",
        "1.21.23.1",
        "1.21.30.3",
        "1.21.31.4"
    };
};
