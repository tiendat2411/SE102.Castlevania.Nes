#pragma once
#include "State.h"

class CHurtingState : public CState
{
public:
	virtual BOOLEAN CanTransition(LPGAMEOBJECT targetObject, sType newState, CharStateConditions* conditions);
	virtual void Enter(LPGAMEOBJECT targetObject);
};
