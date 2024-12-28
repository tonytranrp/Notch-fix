#pragma once

#include <string>
#include <map>
#include "../version.h"
#include "../Utils/Memory.h"
#include "../Client/System/FileSystem.h"
void addOffset(const std::string& functionName, int offset);
void addIndex(const std::string& functionName, int index);
void addSignature(const std::string& functionName, const std::string& signature);
int getOffset(const std::string& functionName);
size_t getIndex(const std::string& functionName);
void* getSig(const std::string& functionName);

class Manager {
public:
    static inline std::set<std::string> targetVersions1_21_X = { 
        "1.21.0.3",
        "1.21.2.2"
    };
    static inline std::set<std::string> targetVersions1_21_2X = { 
        "1.21.20.3",
        "1.21.21.1",
        "1.21.22.1",
        "1.21.23.1"
    };
    static inline std::set<std::string> targetVersions1_21_3X = {
        "1.21.30.3"
        "1.21.31.4"
    };

    static bool checkVer(std::set<std::string> versionList);
    static void init();
};