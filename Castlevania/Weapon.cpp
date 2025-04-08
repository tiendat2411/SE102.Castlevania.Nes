#include "Weapon.h"
#include "Animations.h"


void CWeapon::Render()
{
	int d = 0;
	int saniState = simon->GetAniState();
	if (saniState == SIMON_ANI_DUCKING_ATTACKING_BEGIN || saniState == SIMON_ANI_DUCKING || saniState == SIMON_ANI_JUMPING)
		d = SIMON_HEIGHT_ADJUST;
	CAnimations::GetInstance()->Get(aniState)->Render(x, y + d, directionX);
}