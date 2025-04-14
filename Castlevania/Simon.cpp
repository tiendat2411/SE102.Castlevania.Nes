#include "Simon.h"

#include "Game.h"
#include "Zombie.h"
#include "Brick.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "WalkingState.h"
#include "DuckingState.h"
#include "HurtingState.h"
#include "FallingState.h"
#include "SimonAttackingState.h"

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
	stateConditions->isOnPlatform = false;
}

void CSimon::OnCollisionWith(LPCOLLISIONEVENT e)
{

	 if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0 && dynamic_cast<CBrick*>(e->obj))
			stateConditions->isOnPlatform = true;
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
	left = x - Width / 2 +7;
	top = y - Height / 2;
	right = left + Width - 15;
	bottom = top + Height;
}

void CSimon::Render()
{
	int d = 0;
	if (aniState == SIMON_ANI_DUCKING_ATTACKING_BEGIN || (aniState == SIMON_ANI_DUCKING) )
		d = SIMON_HEIGHT_ADJUST;
	if(currentState == sType::FALLING)
		d = SIMON_HEIGHT_ADJUST;
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

	if (game->IsKeyDown(DIK_RIGHT))
	{
		//if (game->IsKeyDown(DIK_UP))
		//	SetState(sType::WALKING_ONSTAIRS);
		//else if (game->IsKeyDown(DIK_DOWN))
		//		SetState(sType::WALKING_ONSTAIRS);
		//else
		TryChangeState(sType::WALKING, DIRECTION_POSITIVE);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		//if (game->IsKeyDown(DIK_UP))
		//	SetState(sType::ONSTAIRS);
		//else if (game->IsKeyDown(DIK_DOWN))
		//	SetState(sType::ONSTAIRS);
		//else
		TryChangeState(sType::WALKING, DIRECTION_NEGATIVE);
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
	if (isDeleted || stateConditions->isDead) return false;

	LPANIMATION ani = CAnimations::GetInstance()->Get(aniState);
	if (!ani->isAniFinished() && currentState!=sType::WALKING) 
	{ 
		return false; 
	}

	if ( vy > 0 ) {
		newState = sType::FALLING;
	}

	//state transition
	if (states[newState] != nullptr) {
		if (states[currentState]->CanTransition( newState,stateConditions)) {
			if (direction != DIRECTION_DEFAULT) directionX = direction;
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
	return (currentState != sType::DIE);
}

void CSimon::InitAllState() {
	states[sType::IDLE] =new CSimonIdleState();
	states[sType::JUMPING] = new CSimonJumpingState();
	states[sType::WALKING] = new CSimonWalkingState();
	states[sType::DUCKING] = new CSimonDuckingState();
	states[sType::FALLING] = new CSimonFallingState();
	states[sType::ATTACKING] = new  CSimonAttackingState();
	//states[sType::E_HURTING] = new CSimonHurtingState();
	// states[sType::UPSTAIRS] = new CIdleState();
	 //states[sType::DOWNSTAIRS] = new CIdleState();
	currentState = sType::JUMPING;
}