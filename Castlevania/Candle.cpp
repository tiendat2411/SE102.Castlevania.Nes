#include "Candle.h"
#include "AnimationDemo.h"

void Candle::InitAnim()
{
	anim = new AnimationDemo();
	anim->Initialize(sprite, 16, 32, 2, 1, SMALL_CANDLE_ANI_BEGIN, 0.25);


	std::vector<D3DXVECTOR2> animation;
	animation.push_back(D3DXVECTOR2(0, 0));
	animation.push_back(D3DXVECTOR2(1, 0));


	anim->AddAnimation(0, animation);

}

bool Candle::Initialize(LPCWSTR texturePath, float x, float y, int tag, int id)
{
	if (!Enemy::Initialize(texturePath, x, y, tag, id))
		return false;
	return true;
}

void Candle::Render(ViewPort* viewPort)
{
	if (!isDead && isEnable)
		anim->Render(sprite, position, viewPort);
	else
		//deadEffect->Render(viewPort);
		colliderEffect->Render(viewPort);
}

void Candle::Update(float gameTime)
{
	if (!isDead)
	{
		SetBox(sprite->GetPosition().x,
			sprite->GetPosition().y,
			anim->frameWidth,
			anim->frameHeight,
			0,
			0);
		anim->DoAnimation(0);
		anim->Update(gameTime);
	}
	else
		UpdateEffect(gameTime);
	colliderEffect->Update(gameTime);
}

Candle::Candle()
{
}


Candle::~Candle()
{
}
