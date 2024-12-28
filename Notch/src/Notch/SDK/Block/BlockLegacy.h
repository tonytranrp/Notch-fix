#pragma once
#include <string>
#include "../../Libraries/Libs/libhat/libhat.hpp"
class BlockLegacy {
public:
	// BlockLegacy::getBlockItemId(void) | 0x1A6 (1.21.2)
    std::string getName() {
        return hat::member_at<std::string>(this, 0x50);
    }
    int getBlockItemId() {
        return hat::member_at<int>(this, 0x1A6);
    }
};