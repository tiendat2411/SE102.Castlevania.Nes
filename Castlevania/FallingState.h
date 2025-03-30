#pragma once

#include "State.h"
#include "Simon.h"

class CFallingState : public CState
{
public:
	virtual  BOOLEAN StateTransition(CSimon* simon, sType state);
	virtual void Enter(CSimon* simon);

};
