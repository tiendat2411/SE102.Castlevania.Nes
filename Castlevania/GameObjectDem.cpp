#include "GameObjectDem.h"

int GameObjectDem::GetTag()
{
	return tag;
}

CCollider* GameObjectDem::GetCollider()
{
	return collider;
}

void GameObjectDem::SetBox(float x, float y, float w, float h, float vx, float vy)
{
	// Xay dung box collider cho game object
	Box boxCollider;
	boxCollider.top = y;
	boxCollider.bottom = y - h;
	boxCollider.left = x;
	boxCollider.right = x + w;
	boxCollider.vx = vx;
	boxCollider.vy = vy;

	collider->SetBox(boxCollider);
	////////////////////////////////////////
}

D3DXVECTOR2 GameObjectDem::GetVelocity()
{
	return D3DXVECTOR2(0.0f, 0.0f);
}


void GameObjectDem::UpdateEffect(float gameTime)
{
	//deadEffect->SetPosition(sprite->GetPosition().x, sprite->GetPosition().y);
	//deadEffect->Update(gameTime);
	//isDead = !deadEffect->CheckDoAllFrame();
	if (!isDead)
		isEnable = false;
}

GameObjectDem::GameObjectDem()
{
	sprite = NULL;
	region = NULL;
	if (!region)
		region = new RECT();
}

GameObjectDem::~GameObjectDem()
{
	if (sprite)
	{
		delete(sprite);
	}
	if (collider)
		delete(collider);
	if (region)
		delete(region);
}

void GameObjectDem::SetRegion(int left, int right, int top, int bottom)
{
	region->left = position.x + left;
	region->right = position.x + right;
	region->top = position.y + top;
	region->bottom = position.y + bottom;
}

// Is this object's region in another region
bool GameObjectDem::IsInRegion(RECT* region)
{
	if (this->region->right < region->left || this->region->left > region->right ||
		this->region->bottom > region->top || this->region->top < region->bottom)
		return false;
	else
		return true;
}

bool GameObjectDem::Initialize(LPCWSTR texturePath, float _x, float _y, int tag, int _id)
{
	id = 0;
	isEnable = true;
	isDropItem = false;
	isMoveable = false;
	trigger = false;
	isAdded = false;

	if (!sprite)
	{
		sprite = new CSprite(_x, _y);
		if (!sprite->Initialize(texturePath, _id, 1, 1, 1))
			return false;
	}

	collider = new CCollider();

	// Gan tag cho doi tuong
	collider->SetTag(tag);
	this->tag = tag;

	SetSize(sprite->spriteWidth, sprite->spriteHeight);
	SetPosition(sprite->GetPosition());
	SetRegion(0, width, 0, -height);

	isDead = false;

	//deadEffect = new DeadAnimation();
	//deadEffect->Initialize(_gDevice, DEAD_SPRITE, 0, 0);

	colliderEffect = new CColliderEffect();
	colliderEffect->Initialize(COLLIDE_EFFECT_SPRITE, _x, _y - 20);

	// Make copy
	positionC = position;
	regionC = new RECT(*region);

	return true;
}

/*bool GameObjectDem::InitSprite(const char* file, float x, float y)
{
	if (!sprite)
	{
		sprite = new Sprite(x, y);
		if (!sprite->Initialize(gDevice, file))
			return false;
	}
	return true;
}*/

void GameObjectDem::SetSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

void GameObjectDem::SetPosition(D3DXVECTOR2 position)
{
	this->position = position;
}

void GameObjectDem::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}

void GameObjectDem::Render(ViewPort* viewPort)
{
	if (isEnable)
		sprite->Render(viewPort);
}

void GameObjectDem::Update(float gameTime)
{

}

void GameObjectDem::Reload()
{
	isEnable = false;
	isInCamera = false;
	trigger = false;
	sprite->SetPosition(positionC);
	*region = *regionC;
}

bool GameObjectDem::IsInRegionC(RECT* region)
{
	if (this->regionC->right < region->left || this->regionC->left > region->right ||
		this->regionC->bottom > region->top || this->regionC->top < region->bottom)
		return false;
	else
		return true;
}

void GameObjectDem::SetEnable(bool _isEnable)
{
	if (_isEnable)
		isDead = false;
	this->isEnable = _isEnable;
}