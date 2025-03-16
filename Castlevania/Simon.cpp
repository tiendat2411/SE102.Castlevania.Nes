#include "Simon.h"
#include "StateMachine.h"
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// simple fall down
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	DebugOutTitle(L"vx = %0.5f", this->vx);

	CCollision::GetInstance()->Process(this, dt, coObjects);

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
		if (e->ny < 0) isOnPlatform = true;
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
	// SIMON is still on air check, this will not work when SIMON is just stand up
	CStateMachine::GetInstance()->Render(this);
	
}

void CSimon::SetState(sType state, int _directionX)
{
	if (_directionX != DIRECTION_DEFAULT)
		this->directionX = _directionX;
	CStateMachine::GetInstance()->SetState(this, state);
}

