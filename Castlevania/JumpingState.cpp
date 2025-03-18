#include "JumpingState.h"
#include "StateMachine.h"



BOOLEAN CJumpingState::StateTransition(CSimon* simon, sType prevState) 
{

	if (prevState == sType::SIMON_STATE_DUCKING || prevState == sType::SIMON_STATE_ONSTAIRS || simon->isHurting)	return false;

	if (!simon->isAttacking && prevState == sType::SIMON_STATE_JUMPING) 
	{

		return false;
	}
	return true;

}

void CJumpingState::Enter(CSimon* simon) 
{

	if (!simon->isAttacking) 

		simon->SetSpeed(simon->GetVelocityX(), -SIMON_JUMP_SPEED_Y);
	simon->SetAniState((simon->isAttacking) ? SIMON_ANI_STANDING_ATTACKING_BEGIN : SIMON_ANI_JUMPING);
}