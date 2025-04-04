#pragma once

#include <unordered_map>
#include "Attribute.h"
class BaseAttributeMap {
public:
    std::unordered_map<int, AttributeInstance> attributes;
    std::vector<uint64_t> dirtyAttributes;
};

static_assert(sizeof(BaseAttributeMap) == 0x58);