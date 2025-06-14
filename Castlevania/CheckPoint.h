#pragma once
#include "GameObjectDem.h"
class CheckPoint : public GameObjectDem
{
public:
	bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
	CheckPoint();
	~CheckPoint();
};

