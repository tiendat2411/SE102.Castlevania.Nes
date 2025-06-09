#include "JumpingState.h"
#include "StateMachine.h"



BOOLEAN CSimonJumpingState::CanTransition( sType newState, CharStateConditions* conditions)
{
		if (newState==sType::FALLING || newState == sType::ATTACKING)
			return true;
		return false;
}

void CSimonJumpingState::Enter(LPGAMEOBJECT targetObject)
{
	float vx, vy;
	targetObject->GetSpeed(vx, vy);
	targetObject->SetSpeed(targetObject->GetDirectionX() * SIMON_JUMPING_WALKING_SPEED, -SIMON_JUMP_SPEED_Y);
	targetObject->SetAniState(SIMON_ANI_JUMPING);
}