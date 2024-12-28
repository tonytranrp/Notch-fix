#pragma once
#include "BlockLegacy.h"
#include <stdint.h>
class Block {
public:
	BUILD_ACCESS(this, uint8_t, data, 0x8);
	BUILD_ACCESS(this, BlockLegacy*, blockLegacy, 0x10);

	inline BlockLegacy* toLegacy() { return blockLegacy; }
public:
	virtual ~Block();
	virtual int getRenderLayer();
};