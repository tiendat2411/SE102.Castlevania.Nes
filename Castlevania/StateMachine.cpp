//#include "StateMachine.h"
//
//
//void CStateMachine::SetState(CSimon* simon, sType newState) {
//    ULONGLONG now = GetTickCount64();
//    LPANIMATION ani = CAnimations::GetInstance()->Get(simon->GetAniState());
//    if (!ani->isAniFinished() && simon->isAttacking == true) {
//        return;
//    }
//    simon->isAttacking = false;
//
//    //check if attacking
//    if (newState == sType::DEFAULT_STATE) {
//        simon->isAttacking = true;
//        newState = currentState;
//    }
//
//    if (simon->IsOnPlatform() && currentState== sType::SIMON_STATE_HURTING) {
//        simon->isHurting = false;
//
//    }
//
//    if (!simon->IsOnPlatform() && simon->GetVelocityY()>0 && !(newState == sType::SIMON_STATE_HURTING)){
//        newState = sType::SIMON_STATE_FALLING;
//    }
//
//    //state transition
//    if (states[newState] != nullptr) {
//        if (states[newState]->StateTransition(simon, currentState)) {
//            currentState = newState;
//            states[currentState]->Enter(simon);
//        }
//    }
//}
//
//
//void CStateMachine::Init() {
//    states[sType::IDLE] = new CSimonIdleState();
//    states[sType::JUMPING] = new CSimonJumpingState();
//    states[sType::WALKING] = new CSimonWalkingState();
//    states[sType::DUCKING] = new CSimonDuckingState();
//    states[sType::FALLING] = new CSimonFallingState();
//   // states[sType::HURTING] = new CSimonHurtingState();
//    // states[sType::SIMON_STATE_UPSTAIRS] = new CIdleState();
//     //states[sType::SIMON_STATE_DOWNSTAIRS] = new CIdleState();
//}
//CStateMachine::~CStateMachine() {
//    for (auto& state : states) {
//        delete state.second;
//    }
//}
//
//
//
