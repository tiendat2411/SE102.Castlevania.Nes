#pragma once
#include "GameObject.h"


#define LEOPARD_SPEED_RUNNING 0.18f
#define LEOPARD_VYJUMP 0.3f
#define LEOPARD_VXJUMP 0.2f

#define LEOPARD_GRAVITY 0.005f

#define LEOPARD_TRIGGER_DISTANCE 80.0f

class CLeopard :public CGameObject
{
private:

public:
	CLeopard(float x, float y, int directionX);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt);
	int IsCollidable();
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};


