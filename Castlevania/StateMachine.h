//#pragma once
//
//#include "State.h"
//#include "Simon.h"
//#include "IdleState.h"
//#include "JumpingState.h"
//#include "WalkingState.h"
//#include "DuckingState.h"
//#include "HurtingState.h"
//#include "FallingState.h"
//
//
//class CStateMachine {
//private:
//    std::unordered_map<sType, LPSTATE> states;
//    sType currentState;
//
//public:
//    CStateMachine() {}
//    virtual void SetState(CSimon* simon, sType newState)=0;
//	void SetCurrentState(sType newState) { currentState = newState; }
//    sType GetCurrentState() { return currentState; }
//    void Init();
//    ~CStateMachine();
//};
//
//
