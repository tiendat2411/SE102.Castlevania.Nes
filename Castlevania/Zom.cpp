#include "Zom.h"



Zom::Zom(int hp, int damage, int point) : Enemy(hp, damage, point)
{
}


Zom::~Zom()
{
}

bool Zom::Initialize(LPCWSTR texturePath, float x, float y, int tag, int id)
{
	if (!Enemy::Initialize(texturePath, x, y, tag, id))
		return false;

	InitAnimation();

	action = MOVE;

	isLeft = true;

	velocity.x = -70.0f;
	velocity.y = 0;

	return true;
}

void Zom::InitAnimation()
{
	/*anim = new Animation();
	anim->Initialize(sprite, 34, 64, 0.1);

	std::vector<D3DXVECTOR2> moveAnimation;
	moveAnimation.push_back(D3DXVECTOR2(0, 0));
	moveAnimation.push_back(D3DXVECTOR2(1, 0));

	anim->AddAnimation(MOVE, moveAnimation);*/

	anim = CAnimations::GetInstance()->Get(ZOMBIE_ANI_BEGIN);
}

void Zom::Update(float gameTime)
{
	velocity.x = isLeft ? -70 : 70;
	Enemy::GravityHandle(gameTime);
	Enemy::Setbox(0, 0, 0, 0);
	Enemy::Update(gameTime);
}

void Zom::CheckCollider(float gameTime, std::vector<GameObjectDemo*>* listObject)
{
	Enemy::CheckCollider(gameTime, listObject);
	this->CheckColliderWithWall(gameTime, listObject);
}

void Zom::CheckColliderWithWall(float gameTime, std::vector<GameObjectDemo*>* listGameObject)
{
	float normalX = 0;
	float normalY = 0;
	float timeCollide;

	for (std::vector<GameObjectDemo*>::iterator i = listGameObject->begin(); i != listGameObject->end(); i++)
	{
		if ((*i)->GetCollider()->GetTag() == TAG_GROUND)
		{
			Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
			if (collider->AABBCheck(broadphaseBox, (*i)->GetCollider()->GetBox()))
			{
				Box tempBox = (*i)->GetCollider()->GetBox();
				timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), (*i)->GetCollider()->GetBox(), normalX, normalY);
				if ((timeCollide >= 0.0f && timeCollide < 1.0f))
				{
					if (normalX == 1 || normalX == -1)
					{
						isLeft = isLeft ? false : true;
						return;
					}
				}
			}
		}
	}
}