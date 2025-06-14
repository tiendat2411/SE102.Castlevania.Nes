#include "ColliderEffect.h"
#include "Sprite.h"


CColliderEffect::CColliderEffect()
{
}


CColliderEffect::~CColliderEffect()
{
}

bool CColliderEffect::Initialize(LPCWSTR texturePath, float x, float y)
{

	if (!this->sprite)
	{
		sprite = new CSprite(x, y);
		if (!sprite->Initialize(texturePath, 950, 1, 1, 1))
			return false;
	}
	this->timeDelay = 0.0f;
	isVisible = false;
	return true;
}

void CColliderEffect::Render(ViewPort* viewPort)
{
	if (this->isVisible)
		this->sprite->Draw(sprite->position, viewPort);
}

void CColliderEffect::Update(float gameTime)
{
	if (isVisible)
	{
		timeDelay += gameTime;
		if (timeDelay > 0.45f)
		{
			timeDelay = 0.0f;
			isVisible = false;
		}
	}
}

void CColliderEffect::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}