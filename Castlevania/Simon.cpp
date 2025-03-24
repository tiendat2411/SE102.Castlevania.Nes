#include "Simon.h"
#include "StateMachine.h"

#include "Game.h"
#include "Zombie.h"
#include "Brick.h"

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
		if (e->ny < 0 && dynamic_cast<CBrick*>(e->obj))
			isOnPlatform = true;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
			vx = 0;
	}
	/* if (dynamic_cast<CZombie*>(e->obj)) {
		 SetState(sType::SIMON_STATE_HURTING, -directionX);
	 }*/
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
	if (aniState == SIMON_ANI_DUCKING_ATTACKING_BEGIN || (aniState == SIMON_ANI_DUCKING && isOnPlatform) )
		d = SIMON_HEIGHT_ADJUST;
	CAnimations::GetInstance()->Get(aniState)->Render(x, y + d, directionX);
}

void CSimon::SetState(sType state, int _directionX, int _directionY)
{
	if(CStateMachine::GetInstance()->GetCurrentState()==sType::SIMON_STATE_HURTING)
		isHurting = true;

	else
	{
		if (_directionX != DIRECTION_DEFAULT)
			this->directionX = _directionX;
		if (_directionY != DIRECTION_DEFAULT)
			this->directionY = DIRECTION_POSITIVE;
	}
	CStateMachine::GetInstance()->SetState(this, state);
}

int CSimon:: IsCollidable() 
{
	return (CStateMachine::GetInstance()->GetCurrentState() != sType::SIMON_STATE_DIE);
}
