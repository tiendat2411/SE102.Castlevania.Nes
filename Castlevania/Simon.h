#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "debug.h"



class CSimon : public CGameObject
{
	float maxVx, maxVy;
	float ax, ay;
	// acceleration on x 
	BOOLEAN isOnPlatform;
public:
	int Width;
	int Height;
	LPTEXTURE tex;
	BOOLEAN  isAttacking;
	BOOLEAN isDucking;
	BOOLEAN isFalling;
	CSimon(float x, float y) : CGameObject(x, y)
	{
		isDucking= false;
		isAttacking = false;
		isFalling = false;
		maxVx = SIMON_WALKING_SPEED;
		ax = 0.0f;

		maxVy = SIMON_JUMP_SPEED_Y;
		ay = SIMON_GRAVITY;
		directionX = DIRECTION_RIGHT;
		directionY = 1;
		aniState = SIMON_ANI_JUMPING;
		isOnPlatform = false;

		tex = CTextures::GetInstance()->Get(Type::SIMON);

	}

	void SetAcceleration(float ax, float ay = SIMON_GRAVITY) { this->ax = ax, this->ay = ay; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(sType state,int _directionX);

	//Trả về 0 nếu nhân vật không thể va chạm (state = SIMON_STATE_DIE...)
	int IsCollidable()
	{
		return 1;
	}

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	BOOLEAN IsOnPlatform() { return isOnPlatform; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
}; 
