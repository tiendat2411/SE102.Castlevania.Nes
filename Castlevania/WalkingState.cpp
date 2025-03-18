#include "WalkingState.h"
#include "StateMachine.h"


BOOLEAN  CWalkingState::StateTransition(CSimon* simon, sType prevState) {

	if (prevState == sType::SIMON_STATE_DUCKING || !simon->IsOnPlatform() || simon->isHurting)
	{
		return false;
	}
	return true;
}

void CWalkingState::Enter(CSimon* simon) {
	if (simon->isAttacking) 
		SetStaticState(simon);
	else  
		simon->SetAcceleration(simon->GetDirectionX() * SIMON_ACCEL_WALK_X);
	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_STANDING_ATTACKING_BEGIN : SIMON_ANI_WALKING_BEGIN);
}