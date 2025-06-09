#pragma once
#include "State.h"

class CSimonHurtingState : public CState
{
public:
	virtual BOOLEAN CanTransition( sType newState, CharStateConditions* conditions);
	virtual void Enter(LPGAMEOBJECT targetObject);
};
