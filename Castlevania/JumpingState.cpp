#include "JumpingState.h"
#include "StateMachine.h"



BOOLEAN CJumpingState::StateTransition(CSimon* simon, sType prevState) 
{
	if (prevState==sType::SIMON_STATE_DUCKING) 
		return false;
	return true;

}

void CJumpingState::Enter(CSimon* simon) {

	if (simon->GetVelocityX() == SIMON_WALKING_SPEED)
		simon->SetSpeed(SIMON_WALKING_SPEED, -SIMON_JUMP_SPEED_Y);
	else if(simon->GetPosY() >= GROUND_Y)
		simon->SetSpeed(0, -SIMON_JUMP_SPEED_Y);
	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_DUCKING_ATTACKING_BEGIN : SIMON_ANI_JUMPING);
}