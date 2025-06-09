#pragma once

#include "State.h"
#include "Simon.h"
class CSimonAttackingState : public CState
{

public:
	BOOLEAN CanTransition(sType newState, CharStateConditions* conditions);
	void Enter(LPGAMEOBJECT targetObject);

};