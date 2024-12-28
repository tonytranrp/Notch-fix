#pragma once
#include "../../Utils/Memory.h"
#include "Inventory.h"
class PlayerInventory {
public:
	BUILD_ACCESS(this, int, selectedSlot, 0x10);
	BUILD_ACCESS(this, Inventory*, inventory, getOffset("PlayerInventory::inventory"));
};