#include "WalkingState.h"



BOOLEAN  CSimonWalkingState::CanTransition(sType newState, CharStateConditions* conditions) {

	return true;
}

void CSimonWalkingState::Enter(LPGAMEOBJECT targetObject) {

	targetObject->SetSpeed(SIMON_WALKING_SPEED * targetObject->GetDirectionX(), 0);
		//simon->SetSpeed(SIMON_WALKING_SPEED*simon->GetDirectionX(),0);
	targetObject->SetAniState(SIMON_ANI_WALKING_BEGIN);
}