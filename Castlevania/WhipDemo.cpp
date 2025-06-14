#include "WhipDemo.h"



WhipDemo::WhipDemo()
{
}


WhipDemo::~WhipDemo()
{
}

bool WhipDemo::Initialize(LPCWSTR texturePath, float x, float y, int tag, int id)
{
	if (!GameObjectDem::Initialize(texturePath, x, y, tag, id))
		return false;

	anim = new AnimationDemo();
	anim->Initialize(sprite, 240.0f, 66.0f, 3 , 6, (int)Type::WHIP_EDIT, 0.15f);

	std::vector<D3DXVECTOR2> normalWhip;
	normalWhip.push_back(D3DXVECTOR2(0, 0));

	////Khoi tao animation cho roi Vampire Killer
	std::vector<D3DXVECTOR2> vampireKiller;
	vampireKiller.push_back(D3DXVECTOR2(0, 0));
	vampireKiller.push_back(D3DXVECTOR2(1, 0));
	vampireKiller.push_back(D3DXVECTOR2(2, 0));

	//////Khoi tao animation cho roi Chain Whip
	std::vector<D3DXVECTOR2> chainWhip;
	chainWhip.push_back(D3DXVECTOR2(0, 1));
	chainWhip.push_back(D3DXVECTOR2(1, 1));
	chainWhip.push_back(D3DXVECTOR2(2, 1));

	//////Khoi tao animation cho roi Morning Star
	std::vector<D3DXVECTOR2> morningStar;
	morningStar.push_back(D3DXVECTOR2(1, 2));
	morningStar.push_back(D3DXVECTOR2(2, 3));
	morningStar.push_back(D3DXVECTOR2(0, 5));

	anim->AddAnimation(NORMAL_WHIP, normalWhip);
	anim->AddAnimation(VAMPIRE_KILLER, vampireKiller);
	anim->AddAnimation(CHAIN_WHIP, chainWhip);
	anim->AddAnimation(MORNING_STAR, morningStar);

	type = NORMAL_WHIP;
	check = false;
	return true;
}

void WhipDemo::SetType(int _type)
{
	type = _type;
	check = false;
}

void WhipDemo::SetPosition(D3DXVECTOR2 _position, bool isStanding)
{
	_position.x -= 90.0f;
	if (!isStanding)
		_position.y -= 16.5f;
	sprite->SetPosition(_position.x, _position.y);
}

void WhipDemo::SetIsLeft(bool _isLeft)
{
	isLeft = _isLeft;
}

void WhipDemo::Render(ViewPort* viewPort)
{
	anim->Render(isLeft, position, viewPort);
}

void WhipDemo::Update(float gameTime)
{
	anim->DoAnimation(type);
	anim->Update(gameTime);
}

void WhipDemo::CheckCollider(float gameTime, std::vector<GameObjectDem*>* listGameObject)
{
	float normalX = 0;
	float normalY = 0;
	float timeCollide;

	if (!check)
	{
		for (std::vector<GameObjectDem*>::iterator i = listGameObject->begin(); i != listGameObject->end(); i++)
		{
			Box tempBox = (*i)->GetCollider()->GetBox();
			if (collider->AABBCheck(collider->GetBox(), (*i)->GetCollider()->GetBox()))
			{
				if ((*i)->GetTag() < 10 && (*i)->GetTag() >= 0)
				{
					if (((Enemy*)(*i))->e_isInvincible == false)
					{
						((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - GetDamage());
						(*i)->GetCollideEffect()->SetVisible(true);
						check = true;
					}
				}
				else if ((*i)->GetTag() == 2000)
				{
					/*if (((Batman*)(*i))->isHurted == false)
					{
						((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - GetDamage());
						((Batman*)(*i))->isHurted = true;
						(*i)->GetCollideEffect()->SetVisible(true);
						check = true;
					}*/
				}
				else if ((*i)->GetTag() == 2001)
				{
					/*if (((Medusa*)(*i))->isHurted == false)
					{
						((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - GetDamage());
						(*i)->GetCollideEffect()->SetVisible(true);
						check = true;
					}*/
				}
				else
					if ((*i)->GetTag() > 0
						&& (*i)->GetTag() != TAG_GROUND
						&& (*i)->GetTag() != TAG_STAIR
						&& (*i)->GetTag() != 25
						&& (*i)->GetTag() != -25
						&& (*i)->GetTag() != 22
						&& (*i)->GetTag() != -22)
					{
						(*i)->SetDead(true);
						(*i)->GetCollideEffect()->SetVisible(true);
						check = true;
					}
					else if ((*i)->GetTag() == -3)
					{
						(*i)->SetEnable(false);
						check = true;
					}
			}
			/*else
			{
				Box broadphaseBox = collider->GetSweptBoardphaseBox((*i)->GetCollider()->GetBox(), gameTime);
				if (collider->AABBCheck(collider->GetBox(), broadphaseBox))
				{
					Box tempBox = (*i)->GetCollider()->GetBox();
					timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), (*i)->GetCollider()->GetBox(), normalX, normalY);
					if ((timeCollide >= 0.0f && timeCollide < 1.0f))
					{
						if ((*i)->GetTag() < 10 && (*i)->GetTag() >= 0)
						{
							((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - 2);
							(*i)->GetCollideEffect()->SetVisible(true);
						}
						else if ((*i)->GetTag() == 2000)
						{
							if (((Batman*)(*i))->isHurted == false)
							{
								((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - 2);
								((Batman*)(*i))->isHurted = true;
								(*i)->GetCollideEffect()->SetVisible(true);
							}
						}
						else if ((*i)->GetTag() == 2001)
						{
							if (((Medusa*)(*i))->isHurted == false)
							{
								((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - 2);
								(*i)->GetCollideEffect()->SetVisible(true);
							}
						}
						else
							if ((*i)->GetTag() > 0
								&& (*i)->GetTag() != TAG_GROUND
								&& (*i)->GetTag() != TAG_STAIR
								&& (*i)->GetTag() != 25
								&& (*i)->GetTag() != -25
								&& (*i)->GetTag() != 22
								&& (*i)->GetTag() != -22)
							{
								(*i)->SetDead(true);
								(*i)->GetCollideEffect()->SetVisible(true);
								Sound::GetInstance()->Play(HIT_SOUND);
							}
							else if ((*i)->GetTag() == -3)
							{
								(*i)->SetEnable(false);
								Sound::GetInstance()->Play(HIT_SOUND);
							}
					}
				}
			}*/
		}
	}
}

void WhipDemo::CheckColliderWith(float gameTime, GameObjectDem* object)
{
	if (object->IsEnable() == true)
	{
		float normalX = 0;
		float normalY = 0;
		float timeCollide;

		Box tempBox = (object)->GetCollider()->GetBox();
		if (collider->AABBCheck(collider->GetBox(), object->GetCollider()->GetBox()))
		{
			((Enemy*)object)->SetHP(((Enemy*)object)->GetHP() - 2);
			//((Batman*)object)->isHurted = true;
		}
	}
}

