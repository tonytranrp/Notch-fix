#pragma once

class StateVectorComponent
{
public:
	Vec3 Position; //0x0000 
	Vec3 PrevPosition; //0x000C 
	Vec3 Velocity; //0x0018 
};