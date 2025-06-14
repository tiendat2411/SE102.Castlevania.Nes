#pragma once
#include "GameObjectDem.h"


class Ground : public GameObjectDem
{
protected:
	int width;
	int height;

public:
	Ground(int width, int height);
	~Ground();

	bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
	void Render(ViewPort* viewPort);
};

