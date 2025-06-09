#include "SimonAttackingState.h"


BOOLEAN CSimonAttackingState::CanTransition( sType newState, CharStateConditions* conditions) {
	if (newState == sType::ATTACKING) return false;
	return true;
}
void CSimonAttackingState::Enter(LPGAMEOBJECT targetObject) {
	float vx, vy;
	targetObject->GetSpeed(vx, vy);
	if(vy==0)
		SetStaticState(targetObject);
	if(targetObject->GetStateConditions()->isDucking)
		targetObject->SetAniState(SIMON_ANI_DUCKING_ATTACKING_BEGIN);
	else
		targetObject->SetAniState(SIMON_ANI_STANDING_ATTACKING_BEGIN);

}