#include "FallingState.h"
#include "StateMachine.h"



BOOLEAN CFallingState::StateTransition(CSimon* simon, sType prevState) {
	if (simon->isHurting) return false;
	return true;
}

void CFallingState::Enter(CSimon* simon) {
	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_STANDING_ATTACKING_BEGIN : SIMON_ANI_FALLING);
}