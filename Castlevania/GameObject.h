#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>

#include"GameDefines.h"

using namespace std;

class CGameObject
{
protected:
	float x; 
	float y;

	float vx;
	float vy;

	int directionX;	
	int directionY;

	int health;
	Type type;
	int aniState;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void SetAniState(int state) { this->aniState = state; }
	int GetAniState() { return this->aniState; }

	float GetVelocityX() { return vx; }
	float GetVelocityY() { return vy; }
	float GetPosX() { return x; }
	float GetPosY() { return y; }
	int GetDirectionX() { return directionX; }
	int GetDirectionY() { return directionY; }
	int GetHealth() { return health; }
	Type GetType() { return type; }

	CGameObject();
	CGameObject(float x, float y):CGameObject() { this->x = x; this->y = y; }

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	~CGameObject() {};
};

typedef CGameObject* LPGAMEOBJECT;