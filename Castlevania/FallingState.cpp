#include "FallingState.h"
#include "StateMachine.h"



BOOLEAN CSimonFallingState::CanTransition( sType newState, CharStateConditions* conditions) {
	if (!conditions->isOnPlatform || conditions->isHurting) return false;
	return true;
}

void CSimonFallingState::Enter(LPGAMEOBJECT targetObject) {
	targetObject->SetAniState(SIMON_ANI_FALLING);
}