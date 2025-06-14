#pragma once
#include "GameObjectDem.h"

class Stair :
	public GameObjectDem
{
public:
	Stair();
	~Stair();
	bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
};

