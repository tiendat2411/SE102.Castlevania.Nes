/*
#pragma once
#include "GameObject.h"
#include "Simon.h"
class CWhip :public CGameObject
{
private:
	CSimon* simon;
public:

	CWhip(float x, float y ,CSimon* simon) : CGameObject(x, y)
	{
		directionX = DIRECTION_POSITIVE;
		directionY = DIRECTION_POSITIVE;

		aniState = WHIP_ANI_ATTACKING_BEGIN;
		type = Type::SIMON;
		this->simon = simon;

		tex = CTextures::GetInstance()->Get(Type::WHIP);

	}


	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		directionX = simon->GetDirectionX();
		x = simon->GetPosX()+ simon->GetDirectionX()*10; 
		y = simon->GetPosY();
	};	
	void Render(CCamera* camera);

	
	int IsCollidable();

	void OnNoCollision(DWORD dt) {};
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
};

*/