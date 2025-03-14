#pragma once

#include "State.h"

class CJumpingState : public CState
{
public:
	virtual  BOOLEAN StateTransition(CSimon* simon, sType state);
	virtual void Enter(CSimon* simon);

};

