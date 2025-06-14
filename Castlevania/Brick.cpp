//#include "Brick.h"
//
//void CBrick::Render(CCamera* camera)
//{
//	CAnimations* animations = CAnimations::GetInstance();
//	animations->Get(ID_ANI_BRICK)->Render(x,y);
//}
//
////void CBrick::Update(DWORD dt)
////{
////	x += vx * dt;
////	y += vy * dt;
////
////	int backBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
////	float right_edge = backBufferWidth - BRICK_WIDTH;
////	float right_edgeY = CGame::GetInstance()->GetBackBufferHeight() - BRICK_WIDTH;
////	if (x < 0 || x > right_edge) {
////
////		vx = -vx;
////
////		if (x < 0)
////		{
////			x = 0;
////		}
////		else if (x > right_edge)
////		{
////			x = right_edge;
////		}
////	}
////	if (y < 0 || y > right_edgeY) {
////
////		vy = -vy;
////
////		if (y < 0)
////		{
////			y = 0;
////		}
////		else if (y > right_edgeY)
////		{
////			y= right_edgeY;
////		}
////	}
////}
//
//void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
//{
//	Width = tex->getWidth() / tex->_col;
//	Height = tex->getHeight() / tex->_row;
//	l = x - Width / 2;
//	t = y - Height / 2;
//	r = l + Width;
//	b = t + Height;
//}