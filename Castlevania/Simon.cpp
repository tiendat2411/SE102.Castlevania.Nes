#include "Simon.h"

#include "Game.h"
#include "Brick.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "WalkingState.h"
#include "DuckingState.h"
#include "HurtingState.h"
#include "FallingState.h"
#include "SimonAttackingState.h"
#include "DeathState.h"
#include "Whip.h"

#include <algorithm>

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (abs(vx) > abs(maxVx))
		vx = maxVx * directionX;

	if (abs(vy) > abs(maxVy)) vy = maxVy * directionY;
	float MaxX, MaxY;
	CCamera::GetInstance()->GetRange(MaxX, MaxY);
	x = std::clamp(x, 0.0f, MaxX);
	y = std::clamp(y, 0.0f, MaxY);

	DebugOut(L"x,y simon :%02f %0.2f\n", x, y);
	//DebugOutTitle(L"vx = %0.5f", this->vx);
}

void CSimon::OnNoCollision(DWORD dt)
{

	x += vx * dt;
	y += vy * dt;
}

void CSimon::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	 if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;

	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		// DebugOut(L"dir :%d\n", e->obj->IsBlocking());
			vx = 0;

	}


	 if (e->obj->GetType() == Type::ZOMBIE) {
		 if (GetTickCount64() - startHurtingTime >= SIMON_HURTING_TIME) {
			 startHurtingTime = GetTickCount64();
			 SetState(sType::HURTING);
			 this->GetStateConditions()->isHurting = true;
			 health--;
			 
		 }
	 }

	 if (dynamic_cast<CBrick*>(e->obj)) {
		 if (this->GetStateConditions()->isHurting) {
			 SetState(sType::IDLE);
			 this->GetStateConditions()->isHurting = false;
		 }
	 }
	 if (!health) TryChangeState(sType::DIE);

	 
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	Width = tex->getWidth() / tex->_col;
	Height = tex->getHeight() / tex->_row;
	left = x - Width / 2 + 4;
	top = y - Height / 2;
	right = left + Width - 11;
	bottom = top + Height;

	
}

void CSimon::Render()
{
	int d = 0;
	if (aniState == SIMON_ANI_DUCKING_ATTACKING_BEGIN)
		d = SIMON_HEIGHT_ADJUST;
	else if (currentState == sType::DUCKING)
		d = SIMON_HEIGHT_ADJUST;
	ULONGLONG now = GetTickCount64();
	if (((now - startHurtingTime) % 60 > 30 ) && currentState == sType::HURTING) {
		return;
	}
	CAnimations::GetInstance()->Get(aniState)->Render(x, y + d, directionX);
}

void CSimon::ReceiveKeyPress(int keycode) {

	switch (keycode) {
	case DIK_Z:
		TryChangeState(sType::ATTACKING);
		break;
	case DIK_X:
		TryChangeState(sType::JUMPING);
		break;
	case DIK_A:
		TryChangeState(sType::HURTING);
		this->GetStateConditions()->isHurting = true;
		break;
	}
}
void CSimon::ReceiveKeyRelease(int keycode) {	
	switch (keycode) {
	case DIK_DOWN:
		TryChangeState(sType::IDLE);
		break;
	}

}
void CSimon::ControlFromInput(BYTE* states) {
	CGame* game = CGame::GetInstance();

	if (game->IsKeyDown(DIK_LEFT))
	{
		//if (game->IsKeyDown(DIK_UP))
		//	SetState(sType::WALKING_ONSTAIRS);
		//else if (game->IsKeyDown(DIK_DOWN))
		//		SetState(sType::WALKING_ONSTAIRS);
		//else
		TryChangeState(sType::WALKING, DIRECTION_NEGATIVE);
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		//if (game->IsKeyDown(DIK_UP))
		//	SetState(sType::ONSTAIRS);
		//else if (game->IsKeyDown(DIK_DOWN))
		//	SetState(sType::ONSTAIRS);
		//else
		TryChangeState(sType::WALKING, DIRECTION_POSITIVE );
	}
	else 
	{
		TryChangeState(sType::IDLE);

	}

	// Sitting state has higher priority 
	if (game->IsKeyDown(DIK_DOWN))
	{
		TryChangeState(sType::DUCKING);
		stateConditions->isDucking = true;
	}
	else
	{
		stateConditions->isDucking = false;
	}

}
bool CSimon::TryChangeState(sType newState, int direction){

	LPANIMATION ani = CAnimations::GetInstance()->Get(aniState);
	if (!ani->isAniFinished()) 
	{ 
		if(currentState != sType::WALKING && currentState != sType::IDLE)	return false;
	}

	if ( vy > 0 && currentState!=sType::HURTING ) {
		newState = sType::FALLING;
	}

	//state transition
	if (states[newState] != nullptr) {
		if (states[currentState]->CanTransition( newState,stateConditions)) {
			if (direction != DIRECTION_DEFAULT) {
				directionX = direction;
				vx = maxVx * directionX;
			}
				
			SetState(newState);
			return true;
		}
	}
	return false;
}

void CSimon::SetState(sType newState) {
	currentState = newState;
	states[currentState]->Enter(this);
}
int CSimon:: IsCollidable() 
{
	return 1;
}

void CSimon::InitAllState() {
	states[sType::IDLE] =new CSimonIdleState();
	states[sType::JUMPING] = new CSimonJumpingState();
	states[sType::WALKING] = new CSimonWalkingState();
	states[sType::DUCKING] = new CSimonDuckingState();
	states[sType::FALLING] = new CSimonFallingState();
	states[sType::ATTACKING] = new  CSimonAttackingState();
	states[sType::HURTING] = new CSimonHurtingState();
	states[sType::DIE] = new CSimonDeathState();
	// states[sType::UPSTAIRS] = new CIdleState();
	 //states[sType::DOWNSTAIRS] = new CIdleState();
	currentState = sType::JUMPING;
}