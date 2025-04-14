#include "Axe.h"
#include "Animations.h"



void CAxe::OnNoCollision(DWORD dt) {
	if (!isActivate ) {
		x = targetObject->GetPosX();
		y = targetObject->GetPosY() ;
	}
	else {
		x += AXE_SPEED * directionX * dt;
	}

}

void CAxe::Render() {
	if (targetObject->GetCurrentState() == sType::ATTACKING)  isActivate = true;
	if (isActivate)
		CWeapon::Render();
}
void CAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	Width = tex->getWidth() / tex->_col;
	Height = tex->getHeight() / tex->_row;
	left = x - Width / 2;
	top = y - Height / 2 + 16;
	right = left + Width - 84;
	bottom = top + Height - 35;
}


int CAxe::IsCollidable()
{
	return (CAnimations::GetInstance()->Get(AXE_ANI_ATTACKING_BEGIN)->GetCurrentFrame() == AXE_ANI_ATTACKING_END);
}
