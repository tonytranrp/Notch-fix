#pragma once

class AABBShapeComponent
{
public:
	Vec3 PosLower = { 0, 0, 0 }; //0x0000
	Vec3 PosUpper = { 0, 0, 0 }; //0x000C
	Vec2 Hitbox = { 0, 0 }; //0x0018 
};