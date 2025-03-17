#include "StateMachine.h"

CStateMachine* CStateMachine::__instance = NULL;
void CStateMachine::SetState(CSimon* simon, sType newState) {
    LPANIMATION ani = CAnimations::GetInstance()->Get(simon->GetAniState());
    if (!ani->isAniFinished() && simon->isAttacking == true) {
        return;
    }
    simon->isAttacking = false;

    //check if attacking
    if (newState == sType::DEFAULT_STATE) {
        simon->isAttacking = true;
        newState = currentState;
    }

    //set gravity state for simon
    if (!simon->IsOnPlatform()) {
        newState = sType::SIMON_STATE_JUMPING;
        simon->isFalling = true;
    }
    else
        simon->isFalling =false;

    //state transition
    if (states[newState] != nullptr) {
        if (states[newState]->StateTransition(simon, currentState)) {
            currentState = newState;
            states[currentState]->Enter(simon);
        }
    }
}

CStateMachine* CStateMachine::GetInstance() {
    if (__instance == NULL) {
        __instance = new CStateMachine();
        __instance->Init();
    }
    return __instance;
}

void CStateMachine::Init() {
    states[sType::SIMON_STATE_IDLE] = new CIdleState();
    states[sType::SIMON_STATE_JUMPING] = new CJumpingState();
    states[sType::SIMON_STATE_WALKING] = new CWalkingState();
    states[sType::SIMON_STATE_DUCKING] = new CDuckingState();
    // states[sType::SIMON_STATE_UPSTAIRS] = new CIdleState();
     //states[sType::SIMON_STATE_DOWNSTAIRS] = new CIdleState();
    currentState = sType::SIMON_STATE_JUMPING;
}
CStateMachine::~CStateMachine() {
    for (auto& state : states) {
        delete state.second;
    }
}



