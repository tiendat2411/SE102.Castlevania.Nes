#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>

#include"GameDefines.h"
#include "Texture.h"
#include "Collision.h"


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

	int Width;
	int Height;

	int health;
	Type type;
	int aniState;

	LPTEXTURE tex;
	bool isDeleted;
	bool isUpdated;
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }
	bool IsUpdated() { return isUpdated; }
	void SetUpdateState(bool state) { isUpdated = state; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;


	float GetPosX() { return x; }
	float GetPosY() { return y; }
	int GetDirectionX() { return directionX; }
	int GetDirectionY() { return directionY; }

	void SetAniState(int state) { this->aniState = state; }
	int GetAniState() { return this->aniState; }

	float GetVelocityX() { return vx; }
	float GetVelocityY() { return vy; }

	int GetHealth() { return health; }
	Type GetType() { return type; }

	CGameObject();
	CGameObject(float x, float y):CGameObject() { this->x = x; this->y = y; }
	bool operator < (const CGameObject& other) const {
		return this->x < other.x || (this->x == other.x && y < other.y);
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }

	// Is this object collide with other object at certain direction ( like ColorBox )
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }

	~CGameObject();

	static bool IsDeleted(const LPGAMEOBJECT& o) { return o->isDeleted; }

};

typedef CGameObject* LPGAMEOBJECT;