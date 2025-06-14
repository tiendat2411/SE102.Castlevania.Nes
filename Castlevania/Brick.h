//#pragma once
//
//#include "GameObject.h"
//#include "Animation.h"
//#include "Animations.h"
//
//#define ID_ANI_BRICK 3000
//#define BRICK_WIDTH 32
//#define BRICK_BBOX_WIDTH 32
//#define BRICK_BBOX_HEIGHT 32
//
//class CBrick : public CGameObject {
//public:
//	CBrick(float x, float y) : CGameObject(x, y) {
//		tex = CTextures::GetInstance()->Get(Type::BRICK);
//	}
//	CBrick(int id, float x, float y, int width, int height) : CGameObject(id, x, y, width, height) {
//		SetRegion(0, width, 0, -height);
//	}
//	void Render(CCamera* camera);
//	void Update(DWORD dt) {}
//	void GetBoundingBox(float& l, float& t, float& r, float& b);
//};