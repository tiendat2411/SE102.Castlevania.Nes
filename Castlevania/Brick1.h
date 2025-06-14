//#pragma once
//
//#include "GameObject.h" 
//#include "Textures.h"
//#include "Camera.h"
//
//#define BRICK_ID_1 1 // gạch màn 1, 32px
//#define BRICK_ID_2 2 // gạch màn 2,32px
//#define BRICK_ID_3 3 // gạch loại 3, ô nhỏ 16px
//#define BRICK_ID_TRANSPARENT 4 // gạch trong suốt
//#define BRICK_ID_3_3_32 5 // gạch loại 3, 3 ô nhỏ - 32px 
//#define BRICK_ID_3_4_32 6 // gạch loại 3, đủ 4 ô nhỏ - 32px 
//
//class CBrick1 : public CGameObject
//{
//protected:
//	int width;
//	int height;
//	int model;
//
//public:
//	CBrick1 (float X, float Y, int W, int H, int Model);
//	virtual void Render(CCamera* camera);
//	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
//	int GetModel();
//};