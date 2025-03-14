#pragma once

#include <d3dx10.h>
#include <vector>

#include"GameDefines.h"
#include"Animations.h"
#include "Simon.h"


class CState { 
public:
	virtual void Render(CSimon* simon) {
		float x = simon->GetPosX();
		float y = simon->GetPosY();
		float nx = simon->GetDirectionX();

		int aniID = simon->GetAniState();
		int d = 0;
		if (aniID == SIMON_ANI_DUCKING_ATTACKING_BEGIN || aniID == SIMON_ANI_DUCKING)
			d = SIMON_DUCK_HEIGHT_ADJUST;
		CAnimations::GetInstance()->Get(aniID)->Render(x, y+d, nx);

	}

	virtual  BOOLEAN StateTransition(CSimon* simon, sType state) = 0;
	virtual void Enter(CSimon* simon) = 0;

};
typedef CState* LPSTATE;
