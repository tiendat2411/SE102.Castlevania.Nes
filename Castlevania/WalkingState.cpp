#include "WalkingState.h"



BOOLEAN  CSimonWalkingState::CanTransition(sType newState, CharStateConditions* conditions) {

	return true;
}

void CSimonWalkingState::Enter(LPGAMEOBJECT targetObject) {
	float vx, vy;
	targetObject->GetSpeed(vx, vy);
	targetObject->SetSpeed(vx, 0);
	targetObject->SetAniState(SIMON_ANI_WALKING_BEGIN);
}