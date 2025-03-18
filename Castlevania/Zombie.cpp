#include "Zombie.h"
#include "Game.h"
#include "Animations.h"


CZombie::CZombie(float x, float y, int directionX) : CGameObject(x, y) 
{ 
	this->directionX = directionX;
	aniState = ZOMBIE_ANI_BEGIN; 
}

void CZombie::Update(DWORD dt) 
{
	x += vx * dt;
	y += vy * dt;

	vx = ZOMBIE_SPEED_X * this->directionX;
	vy += ZOMBIE_GRAVITY * dt;
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
void CZombie::Render() {
	CAnimations::GetInstance()->Get(aniState)->Render(x, y , directionX);
}