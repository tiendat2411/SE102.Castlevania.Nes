#include "HurtingState.h"
#include "StateMachine.h"



BOOLEAN CHurtingState::CanTransition(LPGAMEOBJECT targetObject, sType newState, CharStateConditions* conditions)
{
		return true;
}

void CHurtingState::Enter(LPGAMEOBJECT targetGameobject)
{

	targetGameobject->SetSpeed(-0.10f * targetGameobject->GetDirectionX(), -SIMON_JUMP_HURT_SPEED_Y);

	targetGameobject->SetAniState(SIMON_ANI_HURTING);
}