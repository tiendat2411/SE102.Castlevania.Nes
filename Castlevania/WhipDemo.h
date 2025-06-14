#pragma once
#include "Enemy.h"
#include "AnimationDemo.h"
//#include "DeadAnimation.h"
//#include "Batman.h"
//#include "Medusa.h"

#define NORMAL_WHIP		0
#define VAMPIRE_KILLER	1
#define CHAIN_WHIP		2
#define MORNING_STAR	3

class WhipDemo : public GameObjectDem
{
private:
	AnimationDemo* anim;
	int type;
	bool isLeft;
	bool check; //kiem tra xem roi da xet va cham chua
public:
	WhipDemo();
	~WhipDemo();

	bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
	void Render(ViewPort* viewPort);
	void Update(float gameTime);

	void SetPosition(D3DXVECTOR2 _position, bool isStanding);

	void SetIsLeft(bool _isLeft);

	void SetType(int _type);

	D3DXVECTOR2 GetVelocity() { return D3DXVECTOR2(0, 0); }

	void CheckCollider(float gameTime, std::vector<GameObjectDem*>* listGameObject);
	void CheckColliderWith(float gameTime, GameObjectDem* object);

	int GetCurrentFrameOfWhip() { return anim->GetCurrentFrame(); }

	int GetDamage() { return type == VAMPIRE_KILLER ? 3 : 4; }
};
