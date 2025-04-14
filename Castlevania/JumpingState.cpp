#include "JumpingState.h"
#include "StateMachine.h"



BOOLEAN CSimonJumpingState::CanTransition( sType newState, CharStateConditions* conditions)
{
	if (!conditions->isOnPlatform) {
		if (newState==sType::FALLING || newState == sType::ATTACKING)
			return true;
		return false;
	}
	return true;

}

void CSimonJumpingState::Enter(LPGAMEOBJECT targetObject)
{
	float vx, vy;
	targetObject->GetSpeed(vx, vy);
	targetObject->SetSpeed(vx, -SIMON_JUMP_SPEED_Y);
	targetObject->SetAniState(SIMON_ANI_JUMPING);
}