#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "debug.h"




#define SIMON_GRAVITY 0.002f 
	
#define SIMON_WALKING_SPEED 0.10f 

#define SIMON_SPEED_ONSTAIR 0.09f 
#define SIMON_ACCEL_WALK_X	0.0005f
#define SIMON_JUMP_SPEED_Y 0.55f
#define SIMON_JUMP_HURT_SPEED_Y 0.30f



#define SIMON_DEFAULT_HEALTH 16
#define SIMON_DEFAULT_HEARTCOLLECT 5
#define SIMON_DEFAULT_SCORE 0
#define SIMON_DEFAULT_LIVES 3


class CSimon : public CGameObject
{
	float maxVx, maxVy;
	float ax, ay;
	
	BOOLEAN isOnPlatform;
public:

	BOOLEAN  isAttacking, isOnStair,isHurting;

	CSimon(float x, float y) : CGameObject(x, y)
	{
		isAttacking = false;
		isOnStair = false;

		isHurting = false;

		maxVx = SIMON_WALKING_SPEED;
		ax = 0.0f;

		maxVy = SIMON_JUMP_SPEED_Y;
		ay = SIMON_GRAVITY;

		directionX = DIRECTION_POSITIVE;
		directionY = DIRECTION_POSITIVE;

		aniState = SIMON_ANI_JUMPING;
		type = Type::SIMON;
		isOnPlatform = false;

		tex = CTextures::GetInstance()->Get(Type::SIMON);

	}
	float GetAccelerationX() { return ax; }
	float GetAccelerationY() { return ay; }
	void SetAcceleration(float ax, float ay = SIMON_GRAVITY) { this->ax = ax, this->ay = ay; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	//Trả về 0 nếu nhân vật không thể va chạm (state = SIMON_STATE_DIE...)
	int IsCollidable();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	BOOLEAN IsOnPlatform() { return isOnPlatform; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(sType state,int _directionX, int _directionY =DIRECTION_POSITIVE);

}; 
