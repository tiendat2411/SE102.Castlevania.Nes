#pragma once
#include "Enemy.h"
#include "Animations.h"
#include "GameObjectDem.h"

class Zom : public Enemy
{
private:
	void InitAnimation();
public:
	Zom(int hp, int damage, int point);
	~Zom();

	bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
	void Update(float gameTime);
	void CheckCollider(float gameTime, std::vector<GameObjectDem*>* listObject);
	void SetIsLeft(bool _isLeft) { isLeft = _isLeft; }
	void CheckColliderWithWall(float gameTime, std::vector<GameObjectDem*>* listGameObject);
};
