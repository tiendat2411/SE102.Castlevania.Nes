#include "HurtingState.h"
#include "StateMachine.h"



BOOLEAN CSimonHurtingState::CanTransition(sType newState, CharStateConditions* conditions)
{
		return false;
}

void CSimonHurtingState::Enter(LPGAMEOBJECT targetGameobject)
{

	targetGameobject->SetSpeed(-SIMON_WALKING_SPEED * targetGameobject->GetDirectionX(), -SIMON_JUMP_HURT_SPEED_Y);


	targetGameobject->SetAniState(SIMON_ANI_HURTING);
}