#include "ItemStack.h"
#include "../../Manager/Manager.h"

bool ItemStack::isValid() const {
    return item.counter != nullptr;
}

Item* ItemStack::getItem() const {
    return item.get();
}

bool ItemStack::isEnchanted() {
    using isEnchantedFunc = bool(__fastcall*)(ItemStack*);
    static auto getIsEnchanted = reinterpret_cast<isEnchantedFunc>(getSig("ItemStack::isEnchanted"));
    return getIsEnchanted(this);
}

short ItemStack::getDamageValue() {
    if (item.counter == nullptr)
        return 0;

    using getDamageValueFunc = short(__fastcall*)(Item*, void*);
    static auto getDamageValue = reinterpret_cast<getDamageValueFunc>(getSig("ItemStack::getDamageValue"));
    return getDamageValue(this->item.get(), this->tag);
}

short ItemStack::getMaxDamage() {
    using getMaxDamageFunc = short(__fastcall*)(ItemStack*);
    static auto getMaxDamage = reinterpret_cast<getMaxDamageFunc>(getSig("ItemStack::getMaxDamage"));
    return getMaxDamage(this);
}