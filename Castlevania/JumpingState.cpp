#include "JumpingState.h"
#include "StateMachine.h"



BOOLEAN CJumpingState::StateTransition(CSimon* simon, sType prevState) 
{
	if (prevState==sType::SIMON_STATE_DUCKING ||( prevState == sType::SIMON_STATE_JUMPING && /*simon->GetPosY() < GROUND_Y*/!simon->IsOnPlatform()))
		return false;
	return true;

}

void CJumpingState::Enter(CSimon* simon) {

		simon->SetSpeed(simon->GetVelocityX(), -SIMON_JUMP_SPEED_Y);

	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_DUCKING_ATTACKING_BEGIN : SIMON_ANI_JUMPING);
}