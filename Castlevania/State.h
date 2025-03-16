#pragma once

#include <d3dx10.h>
#include <vector>

#include"GameDefines.h"
#include"Animations.h"
#include "Simon.h"


class CState { 
public:
	virtual  BOOLEAN StateTransition(CSimon* simon, sType prevState)
	{
		if ( simon->GetPosY() < GROUND_Y &&( prevState == sType::SIMON_STATE_DUCKING || prevState == sType::SIMON_STATE_JUMPING))
		{
			return false;
		}
		return true;
	};
	virtual void Enter(CSimon* simon) = 0;

protected: 
	void SetStaticState(CSimon* simon) 
	{
		simon->SetSpeed(0, 0);
		simon->SetAcceleration(0);
	}

};
typedef CState* LPSTATE;

