#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "debug.h"




#define SIMON_GRAVITY 0.0015f 
	
#define SIMON_WALKING_SPEED 0.15f 
#define SIMON_SPEED_ONSTAIR 0.09f 
#define SIMON_ACCEL_WALK_X	0.0005f
#define SIMON_JUMP_SPEED_Y 0.50f


#define SIMON_DEFAULT_HEALTH 16
#define SIMON_DEFAULT_HEARTCOLLECT 5
#define SIMON_DEFAULT_SCORE 0
#define SIMON_DEFAULT_LIVES 3


class CSimon : public CGameObject
{
	float maxVx, maxVy;
	float ax, ay;
	// acceleration on x 
public:
	BOOLEAN  isAttacking, isOnStair;
	CSimon(float x, float y) : CGameObject(x, y)
	{
		isAttacking = false;
		isOnStair = false;
		maxVx = SIMON_WALKING_SPEED;
		ax = 0.0f;

		maxVy = SIMON_JUMP_SPEED_Y;
		ay = SIMON_GRAVITY;

		directionX = DIRECTION_POSITIVE;
		directionY = DIRECTION_POSITIVE;

		aniState = SIMON_ANI_JUMPING;

	}
	float GetAccelerationX() { return ax; }
	float GetAccelerationY() { return ay; }
	void SetAcceleration(float ax, float ay = SIMON_GRAVITY) { this->ax = ax, this->ay = ay; }
	void Update(DWORD dt);
	void Render();
	void SetState(sType state,int _directionX, int _directionY =DIRECTION_POSITIVE);
}; 
