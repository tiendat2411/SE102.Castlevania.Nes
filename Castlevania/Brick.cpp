#include "Brick.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x,y);
}

void CBrick::Update(DWORD dt)
{
	x += vx * dt;

	int backBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	float right_edge = backBufferWidth - BRICK_WIDTH;

	if (x < 0 || x > right_edge) {

		vx = -vx;

		if (x < 0)
		{
			x = 0;
		}
		else if (x > right_edge)
		{
			x = right_edge;
		}
	}
}