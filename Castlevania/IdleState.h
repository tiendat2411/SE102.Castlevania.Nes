#pragma once

#include "State.h"
#include "Simon.h"
class CSimonIdleState : public CState
{
public:
	virtual BOOLEAN CanTransition( sType newState, CharStateConditions* conditions);
	virtual void Enter(LPGAMEOBJECT targetObject);

};