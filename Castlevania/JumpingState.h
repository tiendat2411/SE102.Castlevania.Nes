#pragma once

#include "State.h"

class CSimonJumpingState : public CState
{
public:
	virtual BOOLEAN CanTransition( sType newState, CharStateConditions* conditions);
	virtual void Enter(LPGAMEOBJECT targetObject);

};

