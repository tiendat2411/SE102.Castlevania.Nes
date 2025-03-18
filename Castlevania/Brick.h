#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 3000
#define BRICK_WIDTH 32
#define BRICK_BBOX_WIDTH 32
#define BRICK_BBOX_HEIGHT 32

class CBrick : public CGameObject {
public:
	int Width;
	int Height;
	LPTEXTURE tex;
	CBrick(float x, float y) : CGameObject(x, y) {
		tex = CTextures::GetInstance()->Get(Type::BRICK);
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};