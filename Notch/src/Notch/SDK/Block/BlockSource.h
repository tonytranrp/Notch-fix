#pragma once
#include "../../Utils/HMath.h"
#include "Block.h"

class BlockActor;
class MaterialType;
class BlockSource {
public:
	virtual void destructor(); // 0
	virtual const Block& getBlock(const Vec3i&, unsigned int) const; // 1
	virtual const Block& getBlock(const Vec3i&) const; // 2
	virtual const Block& getBlock(int, int, int) const; // 3
	virtual BlockActor* getBlockEntity(const Vec3i&); // 4
	virtual const Block& getExtraBlock(const Vec3i&) const; // 5
	virtual const Block& getLiquidBlock(const Vec3i&) const; // 6
	virtual bool hasBlock(const Vec3i&) const; // 7
	virtual bool removeBlock(const Vec3i&); // 8
	virtual bool containsAnyLiquid(const AABB&) const; // 9
	virtual bool containsMaterial(const AABB&, MaterialType) const; // 10
	virtual bool isUnderWater(const Vec3&, const Block&) const; // 11
	//virtual const Material& getMaterial(int, int, int) const; // 12
	//virtual const Material& getMaterial(const Vec3i&) const; // 13
	//virtual bool hasBorderBlock(Vec3i) const; // 14
	//virtual LevelChunk* getChunkAt(const Vec3i&) const; // 15
	//virtual bool hasChunksAt(const AABB&, bool) const; // 16
	//virtual bool hasChunksAt(const Vec3i&, int, bool) const; // 17
	//virtual bool hasChunksAt(const Bounds&, bool) const; // 18
	//virtual AutomaticID<Dimension, int> getDimensionId() const; // 19
	//virtual void fetchAABBs(std::vector<AABB, std::allocator<AABB>>&, const AABB&, bool) const; // 20
	//virtual void fetchCollisionShapes(std::vector<AABB, std::allocator<AABB>>&, const AABB&, bool, optional_ref<const GetCollisionShapeInterface>, std::vector<AABB, std::allocator<AABB>>*) const; // 21
	//virtual void fetchCollisionShapesAndBlocks(std::vector<BlockSourceVisitor::CollisionShape, std::allocator<BlockSourceVisitor::CollisionShape>>&, const AABB&, bool, optional_ref<const GetCollisionShapeInterface>, std::vector<AABB, std::allocator<AABB>>*) const; // 22
	//virtual AABB getTallestCollisionShape(const AABB&, float*, bool, optional_ref<const GetCollisionShapeInterface>) const; // 23
	//virtual float getBrightness(const Vec3i&) const; // 24
	//virtual void postGameEvent(Actor*, const GameEvent&, const Vec3i&, const Block*); // 25
	//virtual std::vector<AABB, std::allocator<AABB>>& fetchAABBs(const AABB&, bool); // 26
	//virtual std::vector<AABB, std::allocator<AABB>>& fetchCollisionShapes(const AABB&, bool, std::optional<const EntityContext>, std::vector<AABB, std::allocator<AABB>>*); // 27
	//virtual WeakRef<BlockSource> getWeakRef(); // 28
	//virtual void addListener(BlockSourceListener&); // 29
	//virtual void removeListener(BlockSourceListener&); // 30
	//virtual gsl::span<gsl::not_null<Actor*>, -1> fetchEntities(ActorType, const AABB&, const Actor*, std::function<bool(Actor*)>); // 31
	//virtual gsl::span<gsl::not_null<Actor*>, -1> fetchEntities(const Actor*, const AABB&, bool, bool); // 32
	//virtual bool setBlock(const Vec3i&, const Block&, int, const ActorBlockSyncMessage*, Actor*); // 33
	//virtual short getMinHeight() const; // 34
	//virtual short getMaxHeight() const; // 35
	//virtual void unknown_36(); // 36
	//virtual void unknown_37(); // 37
	//virtual void unknown_38(); // 38
	//virtual LevelChunk* getChunk(const ChunkPos&) const; // 39
	//virtual LevelChunk* getChunk(int, int) const; // 40
	//virtual void unknown_41(); // 41
	//virtual void unknown_42(); // 42
	//virtual HitResult clip(const Vec3&, const Vec3&, bool, ShapeType, int, bool, bool, Actor*, const std::function<bool(const BlockSource&, const Block&, bool)>&) const; // 43
	//virtual void unknown_44(); // 44
	//virtual bool isSolidBlockingBlock(int, int, int) const; // 45
	//virtual bool isSolidBlockingBlock(const Vec3i&) const; // 46
	//virtual bool areChunksFullyLoaded(const Vec3i&, int) const; // 47
	//virtual bool canDoBlockDrops() const; // 48
	//virtual bool canDoContainedItemDrops() const; // 49
	//virtual bool isInstaticking(const Vec3i&) const; // 50
	//virtual void updateCheckForValidityState(bool); // 51
	//virtual bool checkBlockPermissions(Actor&, const Vec3i&, unsigned char, const ItemStackBase&, bool); // 52
};