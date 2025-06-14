#include "LargeCandle.h"



void LargeCandle::InitAnim()
{
	anim = new AnimationDemo();
	anim->Initialize(sprite, 32, 64, 2, 1, LARGE_CANDLE_ANI_BEGIN, 0.25);


	std::vector<D3DXVECTOR2> animation;
	animation.push_back(D3DXVECTOR2(0, 0));
	animation.push_back(D3DXVECTOR2(1, 0));

	anim->AddAnimation(0, animation);
}

bool LargeCandle::Initialize(LPCWSTR texturePath, float x, float y, int tag, int id)
{
	if (!Enemy::Initialize(texturePath, x, y, tag, id))
		return false;

	InitAnim();
	return true;
}

void LargeCandle::Render(ViewPort* viewPort)
{
	if (!isDead && isEnable)
		anim->Render(sprite, position, viewPort);
	else
	//	deadEffect->Render(viewPort);
	colliderEffect->Render(viewPort);
}

void LargeCandle::Update(float gameTime)
{
	if (!isDead)
	{
		SetBox(sprite->GetPosition().x,
			sprite->GetPosition().y,
			anim->frameWidth,
			anim->frameHeight,
			0,
			0);
		anim->Update(gameTime);
	}
	else
		UpdateEffect(gameTime);
	colliderEffect->Update(gameTime);
}

LargeCandle::LargeCandle()
{
}


LargeCandle::~LargeCandle()
{
}
