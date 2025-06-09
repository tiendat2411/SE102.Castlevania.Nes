#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CTorch : public CGameObject {
public:
	CTorch(float x, float y) : CGameObject(x, y) {
		type = Type::TORCH;
		tex = CTextures::GetInstance()->Get(Type::TORCH);
		health = 1;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)	
	{
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};;
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
};