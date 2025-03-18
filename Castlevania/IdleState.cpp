#include "IdleState.h"
#include "StateMachine.h"



BOOLEAN CIdleState::StateTransition(CSimon* simon,sType prevState) {

	if (!simon->IsOnPlatform()|| simon->isHurting) return false;

	return true;
}

void CIdleState::Enter(CSimon* simon) {
	SetStaticState(simon);
	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_STANDING_ATTACKING_BEGIN :SIMON_ANI_IDLE);
}