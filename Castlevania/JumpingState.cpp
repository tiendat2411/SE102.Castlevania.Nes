#include "JumpingState.h"
#include "StateMachine.h"



BOOLEAN CJumpingState::StateTransition(CSimon* simon, sType prevState) 
{
	if (prevState == sType::SIMON_STATE_DUCKING )	return false;

	if (!simon->isAttacking && (prevState == sType::SIMON_STATE_JUMPING && simon->GetPosY() < GROUND_Y)) {
		return false;
	}
	if (prevState == sType::SIMON_STATE_ONSTAIRS)
	{
		return false;
	}
	return true;

}

void CJumpingState::Enter(CSimon* simon) {
	if (!simon->isAttacking) 
		simon->SetSpeed(simon->GetVelocityX(), -SIMON_JUMP_SPEED_Y);

	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_STANDING_ATTACKING_BEGIN : SIMON_ANI_JUMPING);
}