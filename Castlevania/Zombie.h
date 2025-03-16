#pragma once

#include "GameObject.h"

#define ZOMBIE_SPEED_X 0.09f
#define ZOMBIE_GRAVITY 0.005f

class CZombie:public CGameObject
{
private:

public:
	CZombie(float x, float y, int directionX) : CGameObject(x, y) { this->directionX = directionX; aniState = ZOMBIE_ANI_BEGIN; }
	void Update(DWORD dt);
	void Render();
};

