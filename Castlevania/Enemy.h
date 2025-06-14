#pragma once
#include "GameObjectDem.h"
//#include "AnimationDemo.h"


#define E_INVINCIBLE_TIME 0.4
class AnimationDemo;
class ViewPort;
class Enemy : public GameObjectDem
{
protected:
	AnimationDemo* anim;
	D3DXVECTOR2 velocity;
	float acceleration;

	int action;
	bool isLeft;

	int hp;

	int e_prevHP;
	float e_invincibleTime;

	int hpC;
	int damage;
	int point;

	bool isGravity;
	bool isGrounded;

	static int score;
	void AddScore();
	int type;

public:

	bool e_isInvincible;
	static float stopTime;

	Enemy() {}
	Enemy(int hp, int damage, int point);
	~Enemy();

	virtual bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
	virtual void Render(ViewPort* viewPort);
	virtual void Update(float gameTime);
	virtual void Setbox(float offsetX, float offsetY, float width, float height);
	virtual void CheckCollider(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	virtual bool IsCollideWith(float gameTime, GameObjectDem* object);

	virtual int GetHP() { return this->hp; }
	virtual void SetHP(int hp) { this->hp = hp; }
	int GetPoint() { return point; }

	void Reload();
	void Respawn();

	float respawnTime;
	float respawnTimeNeo;
	bool isIn;

	void GravityHandle(float gameTime);

	static int GetScore();
};

