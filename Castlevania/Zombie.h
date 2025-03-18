#pragma once

#include "GameObject.h"

#define ZOMBIE_SPEED_X 0.1f
#define ZOMBIE_GRAVITY 0.0015f 
class CZombie:public CGameObject
{
private:

public:
	CZombie(float x, float y, int directionX);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) ;
	void OnNoCollision(DWORD dt);
	int IsCollidable();
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

