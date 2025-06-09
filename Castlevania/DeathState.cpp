#include "DeathState.h"
#include "StateMachine.h"


BOOLEAN CSimonDeathState::CanTransition(sType newState, CharStateConditions* conditions) {
	return false;
}
void CSimonDeathState::Enter(LPGAMEOBJECT targetObject) {
	SetStaticState(targetObject);
	targetObject->SetAniState(SIMON_ANI_DEADTH);
}