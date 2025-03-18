#include "HurtingState.h"
#include "StateMachine.h"



BOOLEAN CHurtingState::StateTransition(CSimon* simon, sType prevState)
{
		return true;
}

void CHurtingState::Enter(CSimon* simon)
{

	simon->SetSpeed(-SIMON_WALKING_SPEED *  simon->GetDirectionX(), -SIMON_JUMP_HURT_SPEED_Y);

	simon->SetAniState(SIMON_ANI_HURTING);
}