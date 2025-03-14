#include "IdleState.h"
#include "StateMachine.h"



BOOLEAN CIdleState::StateTransition(CSimon* simon,sType prevState) {

	if (prevState ==sType::SIMON_STATE_JUMPING)
	{
		if (simon->GetPosY() < GROUND_Y)	return false;
	}
	return true;
}

void CIdleState::Enter(CSimon* simon) {
	simon->SetSpeed(0,0);
	simon->SetAcceleration(0);
	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_STANDING_ATTACKING_BEGIN :SIMON_ANI_IDLE);
}