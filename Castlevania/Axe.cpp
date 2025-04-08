#include "Axe.h"
#include "Animations.h"



void CAxe::OnNoCollision(DWORD dt) {
	if (!isActivate ) {
		x = simon->GetPosX();
	}
	else {
		x += AXE_SPEED * directionX * dt;
	}
	y = simon->GetPosY()- 15;
}

void CAxe::Render() {
	if (simon->isAttacking) isActivate = true;
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
