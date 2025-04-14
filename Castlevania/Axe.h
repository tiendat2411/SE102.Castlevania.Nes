#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Weapon.h"


#define AXE_SPEED 0.4f
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
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		CCollision::GetInstance()->Process(this, dt, coObjects);
		if (!isActivate) {
			directionX = targetObject->GetDirectionX();
			return;
		}
		accumulatedTime += dt;
		if (accumulatedTime >= 1000) {
			accumulatedTime = 0;
			isActivate = false;
		}


	};
	void OnNoCollision(DWORD dt);
	void Render();
	int IsCollidable();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

