#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Weapon.h"
#include "Torch.h"
class CWhip :public CWeapon
{
public:

	CWhip(float x, float y , LPGAMEOBJECT target) : CWeapon(x, y, target)
	{
		aniState = WHIP_ANI_ATTACKING_BEGIN;
		type = Type::WHIP;
		tex = CTextures::GetInstance()->Get(Type::WHIP);
		this->x = x;
		this->y = y;

	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

		CCollision::GetInstance()->Process(this, dt, coObjects);
				directionX = targetObject->GetDirectionX();
				directionY = targetObject->GetDirectionY();
				x = targetObject->GetPosX() + targetObject->GetDirectionX() * 14;
				y = targetObject->GetPosY();


	};
	virtual int IsBlocking() { return 0; }
	int IsCollidable();
	void OnNoCollision(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
};

