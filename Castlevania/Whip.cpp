#include "Whip.h"
#include "Simon.h"
#include "Animations.h"


void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	Width = tex->getWidth() / tex->_col;
	Height = tex->getHeight() / tex->_row;
	left = x -30;
	top = y ;
	right = left +Width-10;
	bottom = top +Height/4;
}

void CWhip::OnNoCollision(DWORD dt) {
	//DebugOut(L"x,y :%0.2f  %0.2f // tx,ty :%0.2f  %0.2f \n  ", x,y,targetObject->GetPosX(),targetObject->GetPosY());
}
void CWhip::Render()	
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(WHIP_ANI_ATTACKING_BEGIN);
	if (targetObject->GetCurrentState() == sType::ATTACKING) {
			DebugOut(L"frame:%d \n", ani->GetCurrentFrame());
			CWeapon::Render();
	}
	else
		ani->ReSetCurrentFrame();

	
	
	//DebugOut(L"frame :%d \n", ani->GetCurrentFrame());
}

int CWhip::IsCollidable()
{
	bool isCollidable =  CAnimations::GetInstance()->Get(WHIP_ANI_ATTACKING_BEGIN)->isAniFinished();
	
	return isCollidable;
}
