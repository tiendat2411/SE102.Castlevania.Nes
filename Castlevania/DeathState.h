#pragma once

#include <d3dx10.h>
#include <vector>

#include "GameDefines.h"
#include "State.h"

class CSimonDeathState :public CState {
public:
	virtual BOOLEAN CanTransition(sType newState, CharStateConditions* conditions);
	virtual void Enter(LPGAMEOBJECT targetObject);

};
