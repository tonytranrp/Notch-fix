#include "ConfigManager.h"


void ConfigManager::saveConfig() {
    try {
        std::string path = FileSystem::getClientPath() + xorstr_("\\Configs\\");
        if (!std::filesystem::exists(path))
            std::filesystem::create_directory(path);

        if (moduleMgr != nullptr)
            moduleMgr->onSaveConfig(&currentConfigObj);
        else
            std::cerr << xorstr_("Error: Client or module manager is nullptr\n");

        std::string prefix = xorstr_(".");
        if (prefixMgr != nullptr)
            prefix[0] = *prefixMgr->prefix;
        else
            std::cerr << xorstr_("Error: Client or command manager is nullptr\n");
        currentConfigObj["prefix"] = prefix;

        std::string fullPath = path + currentConfig + xorstr_(".json"); // Changed file extension to .json
        std::ofstream o(fullPath);
        if (o.is_open()) {
            o << std::setw(4) << currentConfigObj.dump(4) << std::endl;
            o.flush();
            o.close();
        }
        else
            std::cerr << xorstr_("Error: Unable to open file for writing: ") << fullPath << std::endl;
   }
    catch (const std::exception& e) {
        std::cerr << xorstr_("Exception in saveConfig(): ") << e.what() << std::endl;
    }
}

void ConfigManager::loadConfig(std::string configName) {
    try {
        std::string path = FileSystem::getClientPath() + xorstr_("\\Configs\\") + configName + xorstr_(".json"); // Changed file extension to .json
        if (!std::filesystem::exists(path)) {
            std::cerr << xorstr_("Error: Config file does not exist: ") << path << std::endl;
            return;
        }

        if (strcmp(configName.c_str(), currentConfig.c_str()) != 0) {
            saveConfig();
        }

        currentConfig = configName;
        std::ifstream confFile(path);
        if (confFile.is_open()) {
            currentConfigObj = json::parse(confFile);
            confFile.close();

            if (moduleMgr != nullptr) {
                moduleMgr->onLoadConfig(&currentConfigObj);
            }
            else {
                std::cerr << xorstr_("Error: Client or module manager is nullptr\n");
            }

            if (currentConfigObj.contains("prefix")) {
                std::string prefix = currentConfigObj["prefix"];
                prefix = prefix.at(0);
                if (!prefix.empty())
                    prefixMgr->prefix = strdup(prefix.c_str());
           }
        }
        else {
            std::cerr << xorstr_("Error: Unable to open file for reading: ") << path << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << xorstr_("Exception in loadConfig(): ") << e.what() << std::endl;
    }
}

ConfigManager* configMgr = new ConfigManager();