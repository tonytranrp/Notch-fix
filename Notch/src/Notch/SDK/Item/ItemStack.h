#pragma once
#include <string_view>
#include <optional>
#include "../Block/BlockLegacy.h"
#include "../../Manager/Manager.h"
#include "../../Utils/Memory.h"
#include "Item.h"
#include "../Misc/WeakPtr.h"
class ItemStack {
public:
    uintptr_t** vtable; // 0x0
    WeakPtr<Item> item; // 0x8
    void* userData;     // 0x10, CompoundTag*
    class Block* block; // 0x18

    BUILD_ACCESS(this, void*, tag, getOffset("ItemStack::tag"));
    BUILD_ACCESS(this, unsigned char, count, getOffset("ItemStack::count"));

    [[nodiscard]] bool isValid() const;
    [[nodiscard]] Item* getItem() const;
    short getDamageValue();
    short getMaxDamage();
    bool isEnchanted();
};