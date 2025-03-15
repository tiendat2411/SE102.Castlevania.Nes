﻿#pragma once

#include "State.h"
#include "Simon.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "WalkingState.h"
#include "UpStairsState.h"
#include "DownStairsState.h"
#include "DuckingState.h"


class CStateMachine {
private:
    static CStateMachine* __instance;
    std::unordered_map<sType, LPSTATE> states;
    sType currentState;

public:
    CStateMachine() :currentState(sType::SIMON_STATE_IDLE) { }
    void SetState(CSimon* simon, sType newState);
    void Render(CSimon* simon);
    static CStateMachine* GetInstance();
    void Init();
    ~CStateMachine();
};


