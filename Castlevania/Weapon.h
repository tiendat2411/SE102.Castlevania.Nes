#pragma once
#include "GameObject.h"
#include "Simon.h"
class CWeapon :public CGameObject
{
protected:
	ULONGLONG lastTimeAttacking;
	LPGAMEOBJECT targetObject;

public:

	CWeapon(float x, float y, LPGAMEOBJECT target) : CGameObject(x, y)
	{
		directionX = DIRECTION_POSITIVE;
		directionY = DIRECTION_POSITIVE;
		targetObject = target;
	}

	virtual int IsBlocking() { return 0; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
			CCollision::GetInstance()->Process(this, dt, coObjects);
	};
	virtual void Render();
	virtual int IsCollidable()=0;
	virtual void OnNoCollision(DWORD dt) = 0;
	virtual void OnCollisionWith(LPCOLLISIONEVENT e)
	{
		if (!e->obj->IsDeleted() && e->obj->GetHealth()) {
			e->obj->Delete();
		}
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)=0;

};

