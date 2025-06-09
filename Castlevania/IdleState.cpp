#include "IdleState.h"
#include "StateMachine.h"



BOOLEAN CSimonIdleState::CanTransition( sType newState, CharStateConditions* conditions) {
	if (conditions->isHurting) return false;
	return true;
}

void;

void CSimonIdleState::Enter(LPGAMEOBJECT targetObject) {
	SetStaticState(targetObject);
	targetObject->SetAniState(SIMON_ANI_IDLE);
}
