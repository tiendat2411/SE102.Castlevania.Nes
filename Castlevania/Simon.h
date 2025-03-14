#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "debug.h"



class CSimon : public CGameObject
{
	float maxVx, maxVy;
	float ax, ay;
	// acceleration on x 
public:
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

	}

	void SetAcceleration(float ax, float ay = SIMON_GRAVITY) { this->ax = ax, this->ay = ay; }
	void Update(DWORD dt);
	void Render();
	void SetState(sType state,int _directionX);
}; 
