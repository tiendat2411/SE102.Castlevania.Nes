#include "DuckingState.h"
#include "StateMachine.h"


BOOLEAN CDuckingState::StateTransition(CSimon* simon, sType prevState) {


	if (prevState == sType::SIMON_STATE_JUMPING) {
		return false;
	}
	return true;
}

void CDuckingState::Enter(CSimon* simon) {
	simon->SetSpeed(0,0);
	simon->SetAcceleration(0);
	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_DUCKING_ATTACKING_BEGIN : SIMON_ANI_DUCKING);
}