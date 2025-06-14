#pragma once

#include "GameObjectDem.h"


class CCamGameObject : public GameObjectDem
{
	int width;
	int height;

public:
	CCamGameObject() {
		this->sprite = NULL;
		this->region = NULL;
		if (!region)
			region = new RECT();
	}
	CCamGameObject(int x, int y) {
		width = x;
		height = y;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Update(DWORD dt, vector<GameObjectDem>* coObjects = NULL) {};
	virtual void Render(ViewPort* viewPort) {};
};
