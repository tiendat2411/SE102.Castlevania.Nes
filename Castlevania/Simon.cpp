#include "Simon.h"
#include "StateMachine.h"

#include "Game.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// simple fall down
	vy += ay * dt;
	vx += ax * dt;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (y < 0) y = 0;
	if (abs(vx) > abs(maxVx)) vx = maxVx * directionX;

	if (abs(vy) > abs(maxVy)) vy = maxVy * directionY;

	DebugOutTitle(L"vx = %0.5f", this->vx);


	// BAD & sinful platform collision handling, see next sample for correct collision handling
	
	int maxX = CGame::GetInstance()->GetBackBufferWidth(), maxY = CGame::GetInstance()->GetBackBufferHeight();


	// simple screen edge collision!!!
	/*if (vx > 0 && x > maxX) x = maxX;
	if (vx < 0 && x < 0) x = 0;

	if (vy > 0 && y > maxY) y = maxY;
	if (vy < 0 && y < 0) y = 0;*/
}

void CSimon::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CSimon::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0)
			isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	Width = tex->getWidth() / tex->_col;
	Height = tex->getHeight() / tex->_row;
	left = x - Width / 2;
	top = y - Height / 2;
	right = left + Width;
	bottom = top + Height;
}
void CSimon::Render()
{
	int d = 0;
	if (aniState == SIMON_ANI_DUCKING_ATTACKING_BEGIN || aniState == SIMON_ANI_DUCKING )
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

int CSimon:: IsCollidable() 
{
	return (CStateMachine::GetInstance()->GetCurrentState() != sType::SIMON_STATE_DIE);
}
