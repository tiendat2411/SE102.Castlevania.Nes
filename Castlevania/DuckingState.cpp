#include "DuckingState.h"
#include "StateMachine.h"


BOOLEAN CSimonDuckingState::CanTransition( sType newState, CharStateConditions* conditions) {

	if (newState == sType::IDLE || newState == sType::ATTACKING) {
		return true;
	}
	return false;
}
void CSimonDuckingState::Enter(LPGAMEOBJECT targetObject) {
	SetStaticState(targetObject);
	targetObject->SetAniState(SIMON_ANI_DUCKING);
}