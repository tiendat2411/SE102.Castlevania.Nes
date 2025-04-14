#include "IdleState.h"
#include "StateMachine.h"



BOOLEAN CSimonIdleState::CanTransition( sType newState, CharStateConditions* conditions) {
	return true;
}

void;

void CSimonIdleState::Enter(LPGAMEOBJECT targetObject) {
	SetStaticState(targetObject);
	targetObject->SetAniState(SIMON_ANI_IDLE);
}
