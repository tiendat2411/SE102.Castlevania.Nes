#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Weapon.h"
class CWhip :public CWeapon
{
public:

	CWhip(float x, float y ,CSimon* simon) : CWeapon(x, y,simon)
	{
		aniState = WHIP_ANI_ATTACKING_BEGIN;
		type = Type::WHIP;
		tex = CTextures::GetInstance()->Get(Type::WHIP);

	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		directionX = simon->GetDirectionX();
		CCollision::GetInstance()->Process(this, dt, coObjects);

	};
	int IsCollidable();
	void OnNoCollision(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
};

