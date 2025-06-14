//#pragma once
//
//#include <Windows.h>
//#include <d3dx10.h>
//#include <vector>
//#include<map>
//#include<string.h>
//
//#include"GameDefines.h"
//#include "define.h"
//#include "Texture.h"
//#include "Collision.h"
////#include "Sprites.h"
//#include "Collider.h"
//#include "ColliderEffect.h"
//#include "ViewPort.h"
////#include "QuadTree.h"
//
//class CQuadTreeNode;
//using namespace std;
//class CCamera;
//class CSprite;
//class CSprites;
//class CGameObject
//{
//protected:
//	int id;
//
//	D3DXVECTOR2 position;
//	float x;
//	float y;
//
//	float vx;
//	float vy;
//
//	int directionX;
//	int directionY;
//
//	int Width;
//	int Height;
//
//	int health;
//	Type type;
//	int aniState;
//	int tag;
//
//	RECT* regionC;
//	D3DXVECTOR2 positionC;
//
//	LPTEXTURE tex;
//	bool isEnable;
//	bool isDead;
//	bool isMoveable;
//	bool isDeleted;
//	bool isUpdated;
//	bool isDynamic;
//	bool isDropItem;
//	bool trigger;
//	bool isAdded;
//	bool isInCamera;
//	CCollider* collider;
//	CColliderEffect* colliderEffect;
//	vector<CQuadTreeNode*> nodeList;
//
//	RECT* region;
//
//	LPTEXTURE texture;
//	LPSPRITE sprite;
//public:
//	void SetPosition(float x, float y) { this->x = x, this->y = y; }
//	void SetPosition(D3DXVECTOR2 position) { this->position = position; }
//	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
//	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
//	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
//
//	virtual void Delete() { isDeleted = true; }
//	bool IsDeleted() { return isDeleted; }
//	bool IsUpdated() { return isUpdated; }
//	void SetUpdateState(bool state) { isUpdated = state; }
//
//	bool IsDynamic() const { return isDynamic; }
//	void SetDynamic(bool dynamic) { isDynamic = dynamic; }
//
//	bool Initialize(LPCWSTR texturePath,float x, float y, int tag, int type, int id, int col, int row, int totalSprites) {
//		
//			isEnable = true;
//			isDropItem = false;
//			isMoveable = false;
//			trigger = false;
//			isAdded = false;
//
//			if (!sprite)
//			{
//				sprite = new CSprite(x, y);
//				if (!sprite->Initialize(texturePath, id, col, row, totalSprites))
//					return false;
//			}
//
//			collider = new CCollider();
//			// Gan tag cho doi tuong
//			collider->SetTag(tag);
//			this->tag = tag;
//			
//			if (type == 0)
//			{
//				Width = 480;
//				Height = 264;
//			}
//			else if (type == 1)
//			{
//				Width = 64;
//				Height = 64;
//			}
//			
//			position.x = x;
//			position.y = y;
//			SetRegion(0, Width, 0, -Height);
//
//			isDead = false;
//
//			colliderEffect = new CColliderEffect();
//			colliderEffect->Initialize(COLLIDE_EFFECT_SPRITE, x, y - 20);
//
//			// Make copy
//			positionC = position;
//			regionC = new RECT(*region);
//
//			return true;
//		
//	}
//
//	CCollider* GetCollider() {
//		return collider;
//	}
//
//	int GetTag()
//	{
//		return tag;
//	}
//
//	void SetBox(float x, float y, float w, float h, float vx, float vy)
//	{
//		Box boxCollider;
//		boxCollider.top = y;
//		boxCollider.bottom = y - h;
//		boxCollider.left = x;
//		boxCollider.right = x + w;
//		boxCollider.vx = vx;
//		boxCollider.vy = vy;
//
//		collider->SetBox(boxCollider);
//	}
//
//	void SetSize(float width, float height)
//	{
//		this->Width = width;
//		this->Height = height;
//	}
//
//
//	D3DXVECTOR2 GetPosition() { return position; }
//
//	vector<CQuadTreeNode*>& GetNodeList() { return nodeList; }
//
//	void AddToNode(CQuadTreeNode* node) {
//		if (!IsInNode(node))
//			nodeList.push_back(node);
//	}
//
//	void ClearNodeList() { nodeList.clear(); }
//
//	bool IsInNode(CQuadTreeNode* node) {
//		return find(nodeList.begin(), nodeList.end(), node) != nodeList.end();
//	}
//
//	void SetRegion(int left, int right, int top, int bottom)
//	{
//		region->left = position.x + left;
//		region->right = position.x + right;
//		region->top = position.y + top;
//		region->bottom = position.y + bottom;
//	}
//
//	bool IsEnable() { return isEnable; }
//
//	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
//
//
//	float GetPosX() { return x; }
//	float GetPosY() { return y; }
//	int GetDirectionX() { return directionX; }
//	int GetDirectionY() { return directionY; }
//
//	void SetAniState(int state) { this->aniState = state; }
//	int GetAniState() { return this->aniState; }
//
//	float GetVelocityX() { return vx; }
//	float GetVelocityY() { return vy; }
//
//	int GetHealth() { return health; }
//	Type GetType() { return type; }
//
//	CGameObject();
//	CGameObject(float x, float y) :CGameObject() { this->x = x; this->y = y; }
//	CGameObject(int id, float x, float y, int Width, int Height) :CGameObject() { this->id = id; this->x = x; this->y = y; this->Width = Width; this->Height = Height; }
//	bool operator < (const CGameObject& other) const {
//		return this->x < other.x || (this->x == other.x && y < other.y);
//	}
//
//	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
//	void Render(CCamera* camera);
//	bool IsInRegion(RECT* region)
//	{
//		if (this->region->right < region->left || this->region->left > region->right ||
//			this->region->bottom > region->top || this->region->top < region->bottom)
//			return false;
//		else
//			return true;
//	}
//	bool IsMoveable() { return this->isMoveable; }
//
//	void SetEnable(bool _isEnable)
//	{
//		if (_isEnable)
//			isDead = false;
//		this->isEnable = _isEnable;
//	}
//
//	virtual RECT* GetRegion() { return region; }
//
//	//
//	// Collision ON or OFF ? This can change depending on object's state. For example: die
//	//
//	virtual int IsCollidable() { return 0; };
//
//	// When no collision has been detected (triggered by CCollision::Process)
//	virtual void OnNoCollision(DWORD dt) {};
//
//	// When collision with an object has been detected (triggered by CCollision::Process)
//	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
//
//	// Is this object blocking other object? If YES, collision framework will automatically push the other object
//	virtual int IsBlocking() { return 1; }
//
//	// Is this object collide with other object at certain direction ( like ColorBox )
//	virtual int IsDirectionColliable(float nx, float ny) { return 1; }
//
//	~CGameObject();
//
//	static bool IsDeleted(const LPGAMEOBJECT& o) { return o->isDeleted; }
//
//};
//
//typedef CGameObject* LPGAMEOBJECT;
