#include "Simon.h"
#include "StateMachine.h"
#include "Game.h"

void CSimon::Update(DWORD dt)
{

	x += vx * dt;
	y += vy * dt;
	// simple fall down
	vy += ay * dt;
	vx += ax * dt;



	if (y > GROUND_Y) {
		y = GROUND_Y; vy = 0;
	}
	if (y < 0) y = 0;
	if (abs(vx) > abs(maxVx)) vx = maxVx * directionX;

	if (abs(vy) > abs(maxVy)) vy = maxVy * directionY;

	DebugOutTitle(L"vx = %0.5f", this->vx);


	// BAD & sinful platform collision handling, see next sample for correct collision handling
	
	int maxX = CGame::GetInstance()->GetBackBufferWidth(), maxY = CGame::GetInstance()->GetBackBufferHeight();
	// simple screen edge collision!!!
	if (vx > 0 && x > maxX) x = maxX;
	if (vx < 0 && x < 0) x = 0;

	if (vy > 0 && y > maxY) y = maxY;
	if (vy < 0 && y < 0) y = 0;

}

void CSimon::Render()
{
	int d = 0;
	if (aniState == SIMON_ANI_DUCKING_ATTACKING_BEGIN || aniState == SIMON_ANI_DUCKING || aniState == SIMON_ANI_JUMPING)
		d = SIMON_HEIGHT_ADJUST;
	CAnimations::GetInstance()->Get(aniState)->Render(x, y + d, directionX);
}

void CSimon::SetState(sType state, int _directionX, int _directionY)
{
	if (_directionX != DIRECTION_DEFAULT)
		this->directionX = _directionX;
	if (_directionY != DIRECTION_DEFAULT)
		this->directionY = 1;
	CStateMachine::GetInstance()->SetState(this, state);
}

