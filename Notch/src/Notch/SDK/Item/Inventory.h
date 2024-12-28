#include "../Item/ItemStack.h"
#include "../Actor/Actor.h"
#include "../Block/Block.h"
#include "../Block/BlockSource.h"

class Inventory {
public:
	virtual void destructor(); // 0
	virtual void init(); // 1
	virtual void serverInitItemStackIds(int, int, __int64); // 2
	virtual void addContentChangeListener(__int64*); // 3
	virtual void removeContentChangeListener(__int64*); // 4
	virtual void addRemovedListener(__int64*); // 5
	virtual void removeRemovedListener(__int64*); // 6
	virtual const ItemStack& getItem(int) const; // 7
	virtual bool hasRoomForItem(const ItemStack&); // 8
	virtual bool addItem(ItemStack&); // 9
	virtual bool addItemWithForceBalance(ItemStack&); // 10
	virtual bool addItemToFirstEmptySlot(const ItemStack&); // 11
	virtual void setItem(int, const ItemStack&); // 12
	virtual void setItemWithForceBalance(int, const ItemStack&, bool); // 13
	virtual void removeItem(int, int); // 14
	virtual void removeAllItems(); // 15
	virtual void removeAllItemsWithForceBalance(); // 16
	virtual void containerRemoved(); // 17
	virtual void dropSlotContent(BlockSource&, const Vec3&, bool, int); // 18
	virtual void dropContents(BlockSource&, const Vec3&, bool); // 19
	virtual int getContainerSize() const; // 20
	virtual int getMaxStackSize() const; // 21
	virtual void unknown_22(); // 22
	virtual void stopOpen(Player&); // 23
	virtual std::vector<ItemStack, std::allocator<ItemStack>> getSlotCopies() const; // 24
	virtual const std::vector<const ItemStack*, std::allocator<const ItemStack*>> getSlots() const; // 25
	virtual int getEmptySlotsCount() const; // 26
	virtual int getItemCount(const ItemStack&) const; // 27
	virtual int findFirstSlotForItem(const ItemStack&) const; // 28
	virtual void unknown_29(); // 29
	virtual void unknown_30(); // 30
	virtual void setContainerChanged(int); // 31
	virtual void setContainerMoved(); // 32
	virtual void setCustomName(std::string&); // 33
	virtual bool assumeSymmetry() const; // 34
	virtual void readAdditionalSaveData(/*const CompoundTag&*/); // 35
	virtual void addAdditionalSaveData(/*CompoundTag&*/); // 36
	virtual void createTransactionContext(/*std::function<void(Container&, int, const ItemStack&, const ItemStack&)>, std::function<void()>*/); // 37
	virtual void unknown_38(); // 38
	virtual bool isEmpty() const; // 39
	virtual bool hasGetStrictParsingVersion(); // 40
	virtual bool add(ItemStack&); // 41
	virtual bool canAdd(const ItemStack&) const; // 42
	virtual void clearSlot(int); // 43
	virtual int clearInventory(int); // 44
	virtual void load(/*const ListTag&, const SemVersion&, Level&*/); // 45
	virtual int getFirstEmptySlot() const; // 46
	virtual void setContainerSize(int); // 47
};