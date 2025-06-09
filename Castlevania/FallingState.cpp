#include "FallingState.h"
#include "StateMachine.h"



BOOLEAN CSimonFallingState::CanTransition( sType newState, CharStateConditions* conditions) {
	return true;
}

void CSimonFallingState::Enter(LPGAMEOBJECT targetObject) {
		targetObject->SetAniState(SIMON_ANI_FALLING);
}