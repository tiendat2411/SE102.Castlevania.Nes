/*#pragma once
//#include "GameObject.h"

#include "Animation.h"
#include "debug.h"


#define INVINCIBLE_TIME 2

#define SIMON_GRAVITY 0.002f 
	
#define SIMON_WALKING_SPEED 0.10f 

#define SIMON_SPEED_ONSTAIR 0.09f 
#define SIMON_ACCEL_WALK_X	0.0005f
#define SIMON_JUMP_SPEED_Y 0.6f
#define SIMON_JUMP_HURT_SPEED_Y 0.450f



#define SIMON_DEFAULT_HEALTH 16
#define SIMON_DEFAULT_HEARTCOLLECT 5
#define SIMON_DEFAULT_SCORE 0
#define SIMON_DEFAULT_LIVES 3

class CGameObject;
class CSimon : public CGameObject
{
	int hp;
	int prevHP;
	float maxVx, maxVy;
	float ax, ay;
	bool isLeft;
	bool isGrounded;
	D3DXVECTOR2 velocity;
	int action;
	bool isInvincible;
	float invincibleTime;
	bool canControlKeyboard;
	int noSubWeapon = 1;
	

	BOOLEAN isOnPlatform;
public:
	int score = 0;
	int energy = 0;
	int life = 3;
	int currentWeapon;
	bool nextStage;
	bool isGravity;

	bool isCollideLeftWall;
	bool isCollideRightWall;

	D3DXVECTOR2 stairCollidePos;
	bool isCollideWith25; // 25 la tag cua chan cau thang
	bool isCollideWith_25; // -25 la tag cua chan cau thang tu phai qua trai
	bool isCollideWith22; // 22 la tag cua top cau thang LTR
	bool isCollideWith_22; 

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
	void Render(CCamera* camera);

	//Trả về 0 nếu nhân vật không thể va chạm (state = SIMON_STATE_DIE...)
	int IsCollidable();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	BOOLEAN IsOnPlatform() { return isOnPlatform; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool IsColliderWithCheckPoint(float gameTime, std::vector<CGameObject*>* listGameObject);
	void Reset(D3DXVECTOR2 pos);

	void SetState(sType state,int _directionX, int _directionY =DIRECTION_POSITIVE);
	virtual void SetHP(int hp) { this->hp = hp; }
	int GetScore();

	int GetHP() { return this->hp; }
	int GetEnergy() { return this->energy; }
	int GetLife() { return life; }
	int GetNoSubWeapon() { return noSubWeapon; }
	D3DXVECTOR2 GetVelocity();
	void Reload();
}; 
*/