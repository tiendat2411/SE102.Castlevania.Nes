#pragma once
#include<vector>
#include "GameObject.h"
#include "State.h"

#include "Animation.h"
#include "debug.h"






class CSimon : public CGameObject
{
	float maxVx, maxVy;
	float ax, ay;
	std::unordered_map<sType, LPSTATE> states;

public:

	CSimon(float x, float y) : CGameObject(x, y)
	{
		InitAllState();
		SetState(sType::FALLING);

		maxVx = SIMON_WALKING_SPEED;
		ax = 0.0f;

		maxVy = SIMON_JUMP_SPEED_Y;
		ay = SIMON_GRAVITY;
		type = Type::SIMON;

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
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);


	void ReceiveKeyPress(int keycode);
	void ReceiveKeyRelease(int keycode);
	void ControlFromInput(BYTE* states);

	void SetState(sType newState);
	bool TryChangeState(sType newState,int direction = DIRECTION_DEFAULT);

	void InitAllState();

}; 
