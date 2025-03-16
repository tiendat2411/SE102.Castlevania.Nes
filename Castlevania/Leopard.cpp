#include "Leopard.h"
#include "Animations.h"
#include "Simon.h"

extern CSimon* simon;

CLeopard::CLeopard(float x, float y, int directionX) : CGameObject(x, y)
{
	this->directionX = directionX;
	aniState = LEOPARD_ANI_IDLE;
}

void CLeopard::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	vx = LEOPARD_SPEED_RUNNING * this->directionX;
	vy += LEOPARD_GRAVITY * dt;
	if (y > GROUND_Y) {
		y = GROUND_Y; vy = 0;
	}

	int maxX = CGame::GetInstance()->GetBackBufferWidth(), maxY = CGame::GetInstance()->GetBackBufferHeight();
	// simple screen edge collision!!!
	if (vx > 0 && x > maxX) {
		x = maxX; directionX = -directionX;
	}
	if (vx < 0 && x < 0) {
		x = 0; directionX = -directionX;
	}
}
void CLeopard::Render() {
	CAnimations::GetInstance()->Get(aniState)->Render(x, y, directionX);
}