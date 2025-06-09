#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Weapon.h"


#define AXE_SPEED 0.2f
class CAxe :public CWeapon
{
private:
	ULONGLONG accumulatedTime;
	bool isActivate;
public:

	CAxe(float x, float y, LPGAMEOBJECT target) : CWeapon(x, y, target)
	{
		aniState = AXE_ANI_ATTACKING_BEGIN;
		type = Type::AXE;
		tex = CTextures::GetInstance()->Get(Type::AXE);
		x = targetObject->GetPosX();
		accumulatedTime = 0;
		isActivate = false;

	}
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		
		if (!isActivate) {
			directionX = targetObject->GetDirectionX();
			return;
		}
		accumulatedTime += dt;
		if (accumulatedTime >= 1000) {
			accumulatedTime = 0;
			isActivate = false;
		}
		CCollision::GetInstance()->Process(this, dt, coObjects);

	};
	void OnNoCollision(DWORD dt);
	void Render();
	int IsCollidable();
	int isBlocking() { return 0; };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

