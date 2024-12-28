#pragma once
class MaterialPtr;
class LevelRendererPlayer {
public:
	BUILD_ACCESS(this, Vec3, cameraPos, getOffset("LevelRendererPlayer::cameraPos"));
};

class LevelRenderer {
public:
	LevelRendererPlayer* getLevelRendererPlayer()
	{
		return *reinterpret_cast<LevelRendererPlayer**>((uintptr_t)(this) + 0x308);
		/*
		* v8 = *(_DWORD **)(v7 + 0x308);
		*(_DWORD *)(a1 + 132) = v8[383];
		*(_DWORD *)(a1 + 136) = v8[384];
		 (_DWORD *)(a1 + 140) = v8[385];
		*/
	};

	Vec3 getOrigin() {
		return getLevelRendererPlayer()->cameraPos;
	};
};