//#include "StandingOnStairsState.h"
//#include "StateMachine.h"
//
//
//
//void CStandingOnStairsState::Enter(CSimon* simon) {
//	SetStaticState(simon);
//	if (simon->GetDirectionY() == DIRECTION_NEGATIVE) {
//		simon->SetAniState((simon->isAttacking) ? SIMON_ANI_STAIR_UP_ATTACKING_BEGIN : SIMON_ANI_STAIR_STANDING_UP);
//	}
//	else
//		simon->SetAniState((simon->isAttacking) ? SIMON_ANI_STAIR_DOWN_ATTACKING_BEGIN : SIMON_ANI_STAIR_STANDING_DOWN);
//	simon->SetAcceleration(0, 0);
//	simon->SetSpeed(simon->GetDirectionX() * 0.09f, simon->GetDirectionY() * 0.09f);
//}