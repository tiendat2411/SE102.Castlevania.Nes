#pragma once
#include "GameObjectDem.h"
class SceneCheck :
	public GameObjectDem
{
public:
	bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
	SceneCheck();
	~SceneCheck();
};

