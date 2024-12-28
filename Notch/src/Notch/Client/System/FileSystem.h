#pragma once
#include <windows.h>
#include <iostream>
#include <direct.h>
#include <string>
#include <iomanip>
#include "../../Libraries/Libraries.h"
#include "../../Utils/StringUtil.h"
#include "../../Utils/Logger.h"

#include <filesystem>

#include "Network.h"

namespace fs = std::filesystem;
class FileSystem {
public:
	static void Initalize();

	static void createFolder(std::string folderName);
	static void createAssetsFolder(std::string assetsFolderName);
	static std::string getRoamPath() {
		char* value;
		size_t size;

		_dupenv_s(&value, &size, xorstr_("APPDATA"));

		std::string roam = (value + std::string(xorstr_("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\")));
		return roam;
	}
	static std::string getClientPath() {
		return getRoamPath() + xorstr_("\\Notch");
	}
};