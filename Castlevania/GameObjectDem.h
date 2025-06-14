#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "Collider.h"
// #include "DeadAnimation.h"
#include "ColliderEffect.h"
#include "define.h"
#include "GameDefines.h"

class CSprite;
typedef CSprite* LPSPRITE;
class ViewPort;
class GameObjectDem
{
private:
	int tag;
	int id;
protected:
	
	CCollider* collider;
	RECT* region;
	float width;
	float height;
	D3DXVECTOR2 position;
	bool isEnable;
	bool isDead;
	bool isMoveable;

	//DeadAnimation* deadEffect;
	CColliderEffect* colliderEffect;

public:
	LPSPRITE sprite;
	bool isInCamera;
	bool trigger;
	RECT* regionC;
	D3DXVECTOR2 positionC;
	bool isAdded;

	virtual bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
	virtual bool Initialize(const char* file, float x, float y, int tag);
	virtual bool InitSprite(const char* file, float x, float y);
	virtual void Render(ViewPort* viewPort);
	virtual void Update(float gameTime);

	int GetTag();
	CCollider* GetCollider();

	virtual void SetBox(float x, float y, float w, float h, float vx, float vy);

	virtual D3DXVECTOR2 GetVelocity();

	// For interact with quadTree
	virtual bool IsInRegion(RECT* region);
	virtual bool IsInRegionC(RECT* region);
	virtual void SetRegion(int left, int right, int top, int bottom);
	virtual RECT* GetRegion() { return region; }
	virtual void CheckCollider(float gameTime, std::vector<GameObjectDem*>* listGameObject) {}

	float GetWidth() { return width; }
	float GetHeight() { return height; }
	D3DXVECTOR2 GetPosition() { return this->sprite->GetPosition(); }
	void SetSize(float width, float height);
	void SetPosition(D3DXVECTOR2 position);
	void SetPosition(float x, float y);

	void SetEnable(bool enable);
	bool IsEnable() { return isEnable; }

	void SetDead(bool _isDead) { isDead = _isDead; }
	bool IsDead() { return isDead; }

	void UpdateEffect(float gameTime);

	CColliderEffect* GetCollideEffect() { return colliderEffect; }

	void SetID(int id) { this->id = id; }
	int GetID() { return id; }
	GameObjectDem();
	~GameObjectDem();

	void SetMoveable(bool isMoveable) { this->isMoveable = isMoveable; }
	bool IsMoveable() { return this->isMoveable; }
	virtual void Reload();

	bool isDropItem;

	//void SetColor(D3DCOLOR color) { sprite->SetColor(color); }
};

