#include "Whip.h"
#include "Simon.h"
#include "StateMachine.h"


void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	Width = tex->getWidth() / tex->_col;
	Height = tex->getHeight() / tex->_row;
	left = x - Width / 2;
	top = y - Height / 2 + 16;
	right = left + Width - 84 ;
	bottom = top + Height - 35;
}

void CWhip::OnNoCollision(DWORD dt) {
	x = simon->GetPosX() + simon->GetDirectionX() * 10;
	y = simon->GetPosY();
}
void CWhip::Render()
{
	if (!simon->isAttacking) return;
	CWeapon::Render();
}

int CWhip::IsCollidable()
{
	return (CAnimations::GetInstance()->Get(WHIP_ANI_ATTACKING_BEGIN)->GetCurrentFrame()== WHIP_ANI_ATTACKING_END);
}
