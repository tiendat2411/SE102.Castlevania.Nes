#include "SimonAttackingState.h"


BOOLEAN CSimonAttackingState::CanTransition( sType newState, CharStateConditions* conditions) {
	return true;
}
void CSimonAttackingState::Enter(LPGAMEOBJECT targetObject) {
	if(targetObject->GetStateConditions()->isOnPlatform)
		SetStaticState(targetObject);
	if(targetObject->GetStateConditions()->isDucking)
		targetObject->SetAniState(SIMON_ANI_DUCKING_ATTACKING_BEGIN);
	else
		targetObject->SetAniState(SIMON_ANI_STANDING_ATTACKING_BEGIN);

}