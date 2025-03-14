#include "WalkingState.h"
#include "StateMachine.h"


BOOLEAN CWalkingState::StateTransition(CSimon* simon, sType prevState) {

	if (prevState == sType::SIMON_STATE_IDLE || prevState == sType::SIMON_STATE_WALKING)
	{
		return true;
	}
	return false;
}

void CWalkingState::Enter(CSimon* simon) {
	if (simon->isAttacking) {
		simon->SetSpeed(0, 0);
		simon->SetAcceleration(0);
	}
	else 
		simon->SetAcceleration(simon->GetDirectionX() * SIMON_ACCEL_WALK_X);
	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_STANDING_ATTACKING_BEGIN : SIMON_ANI_WALKING_BEGIN);
}