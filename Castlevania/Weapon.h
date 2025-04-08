#pragma once
#include "GameObject.h"
#include "Simon.h"
class CWeapon :public CGameObject
{
protected:
	ULONGLONG lastTimeAttacking;
	CSimon* simon;
public:

	CWeapon(float x, float y, CSimon* simon) : CGameObject(x, y)
	{
		directionX = DIRECTION_POSITIVE;
		directionY = DIRECTION_POSITIVE;
		this->simon = simon;
	}


	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)=0;
	virtual void Render();
	virtual int IsCollidable()=0;
	virtual void OnNoCollision(DWORD dt) = 0;
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)=0;

};

