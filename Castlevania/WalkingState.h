#pragma once

#include "State.h"

class CWalkingState: public CState
{
public :
	virtual  BOOLEAN StateTransition(CSimon* simon, sType state);
	virtual void Enter(CSimon* simon);

};

