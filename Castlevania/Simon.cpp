#include "Simon.h"
#include "StateMachine.h"

void CSimon::Update(DWORD dt)
{

	x += vx * dt;
	y += vy * dt;
	// simple fall down
	vy += SIMON_GRAVITY * dt;
	vx += ax * dt;



	if (y > 100) {
		y = 100;
	}
	if (y < 0) y = 0;
	if (abs(vx) > abs(maxVx)) vx = maxVx * directionX;

	if (abs(vy) > abs(maxVy)) vy = maxVy * directionY;

	DebugOutTitle(L"vx = %0.5f", this->vx);


	// BAD & sinful platform collision handling, see next sample for correct collision handling
	

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;

	if (vy > 0 && y > 290) y = 1000;
	if (vy < 0 && y < 0) y = 0;

}

void CSimon::Render()
{
	// SIMON is still on air check, this will not work when SIMON is just stand up
	CStateMachine::GetInstance()->Render(this);
	
}

void CSimon::SetState(sType state, int _directionX)
{
	if (_directionX != DIRECTION_DEFAULT)
		this->directionX = _directionX;
	CStateMachine::GetInstance()->SetState(this, state);
}

