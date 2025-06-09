#pragma once

#include <d3dx10.h>
#include <vector>

#include"GameDefines.h"
#include"Animations.h"

#include "GameObject.h"


class CState { 

public:
	virtual  BOOLEAN CanTransition(sType newState, CharStateConditions* conditions) =0;
	virtual void Enter(LPGAMEOBJECT targetObject) =0;
	void SetStaticState(LPGAMEOBJECT targetObject)
	{
		targetObject->SetSpeed(0, 0);
	}
};
typedef CState* LPSTATE;
