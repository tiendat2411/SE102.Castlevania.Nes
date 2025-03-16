#pragma once

#include "State.h"
#include "Simon.h"
class CStandingOnStairsState: public CState
{
public:
	virtual void Enter(CSimon* simon);

};
