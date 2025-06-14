#pragma once
//#include "GameObjectDem.h"
#include "Animation.h"
#include "AnimationDemo.h"
#include "Input.h"
#include "Collider.h"
//#include "Enemy.h"
#include "WhipDemo.h"
//#include "MovableGround.h"
//#include "Sound.h"
//#include "Batman.h"
//#include "HolyWater.h"
//#include "Cross.h"
//#include "Axe.h"
//#include "Knife.h"
//#include "Door.h"
//#include "StopWatch.h"

#define INVINCIBLE_TIME 2

class Enemy;
class SimonDemo : public Enemy
{
private:
	int noSubWeapon;

	int currentAnimID;

	float simonSpeed;

	WhipDemo* whip;

	//SubWeapon* axe[3];
	//SubWeapon* cross[3];
	//SubWeapon* holyWater[3];
	//SubWeapon* knife[3];
	//SubWeapon* stopWatch[3];

	bool isFighting;
	bool isThrowing;

	bool isCollideWithBottomStair;
	bool isCollideWithTopStair;

	bool isOnStair;

	bool isCollideLeftWall;
	bool isCollideRightWall;

	D3DXVECTOR2 stairCollidePos;
	bool isCollideWith25; // 25 la tag cua chan cau thang
	bool isCollideWith_25; // -25 la tag cua chan cau thang tu phai qua trai
	bool isCollideWith22; // 22 la tag cua top cau thang LTR
	bool isCollideWith_22; // -22 la tag cua cau thang RTL

	bool isInvincible;
	float invincibleTime;
	int directionX = 0, directionY = 0;

	int typeOfSubWeapon;
	int typeOfWhip;
	int energy;

	bool isSplashing;

	bool canControlKeyboard;

	int life;
	int prevHP;

	/*bien nay dung de xac dinh vua roi simon di len hay xuong cau thang*/
	int currentDirection; // -1 0 1 , xuong - len

	D3DXVECTOR2 collideDoor;
	//Door* door;
	int doorCollideDirection;
	bool isGoingThrowDoor;
	D3DXVECTOR2 viewportCheckpoint;

	float timeCollideGround;

	float deadTime;
public:
	//SubWeapon* subWeapon[3];

	int currentWeapon;
	static int score;

	D3DXVECTOR2 simonCheckpoint;
	SimonDemo(int hp, int damage, int point);
	~SimonDemo();
	bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
	void Reload();
	void Render(ViewPort* viewPort);

	void SetPrevHP(int preHp) { this->prevHP = preHp; }

	void CreateAnimation();
	void Update(float gameTime);

	void UpdateKeyboard(float gameTime);
	void Move();
	void Jump();
	void Sit();
	void Stand();
	void Fight();
	void Fighting();
	void Throwing();
	void StandOnStair();
	void KeyBoardHandle(float gameTime);
	void Hurted();

	D3DXVECTOR2 GetVelocity();
	void SetVelocity(D3DXVECTOR2 vel) { velocity = vel; }

	void CheckCollideWithGround(float gameTime, GameObjectDem* gameObject);
	void CheckCollideWithGround(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	void CheckCollider(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	void CheckCollideWithStair(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	void CheckCollideWithWall(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	void CheckCollideWithEnemy(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	void CheckColliderWithMovableGround(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	bool IsCollideWith(float gameTime, GameObjectDem* object);
	void CheckColliderWith(float gameTime, GameObjectDem* object);
	void WhipCheckCollider(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	void CheckColliderWithDoor(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	bool IsColliderWithCheckPoint(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	void CheckCollieWithTopStair(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	void ChangeSenceStairCheck(float gameTime, std::vector<GameObjectDem*>* listGameObject, ViewPort* viewPort);

	void CollideWithDoorHandle(float gameTime, std::vector<GameObjectDem*>* listGameObject, ViewPort* viewPort);

	WhipDemo* GetWhip() { return whip; }

	bool GetIsFighting() { return isFighting; }

	bool GetIsLeft() { return isLeft; }

	void SetIsLeft(bool status) { isLeft = status; }

	bool IsInvincible() { return isInvincible; }

	bool IsOnStair() { return isOnStair; }

	int GetAction() { return action; }

	void SetAction(int action) { this->action = action; }

	int GetNoSubWeapon() { return noSubWeapon; }

	//SubWeapon** GetSubWeapon(int i) { return subWeapon; }

	void SetTypeOfWhip(int typeOfWhip) { this->typeOfWhip = typeOfWhip; }

	int GetTypeOfWhip() { return this->typeOfWhip; }

	void SetEnergy(int energy) { this->energy = energy; }

	int GetEnergy() { return this->energy; }

	void SetTypeOfSubWeapon(int subType);

	void SetNoSubWeapon(int no) { noSubWeapon = no; }

	//SubWeapon* GetSubWeaponType(int typeOfSubWeapon);

	void Reset(D3DXVECTOR2 pos);

	int GetLife() { return life; }

	void OnStairHandle(float gameTime);

	void SetInvincible(int time);

	bool nextStage;

	D3DXVECTOR2 GetCollideDoor() { return collideDoor; }

	void SetCanControlKeyboard(bool status) { canControlKeyboard = status; }

	bool CanControllKeyboard() { return canControlKeyboard; }

	bool IsGoingThrowDoor() { return isGoingThrowDoor; }
};


