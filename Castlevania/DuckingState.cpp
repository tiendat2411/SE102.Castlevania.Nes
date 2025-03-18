#include "DuckingState.h"
#include "StateMachine.h"


BOOLEAN CDuckingState::StateTransition(CSimon* simon, sType prevState) {


	if (prevState == sType::SIMON_STATE_JUMPING || prevState == sType::SIMON_STATE_ONSTAIRS || simon->isHurting) {
		return false;
	}
	return true;
}

void CDuckingState::Enter(CSimon* simon) {
	SetStaticState(simon);
	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_DUCKING_ATTACKING_BEGIN : SIMON_ANI_DUCKING);
}