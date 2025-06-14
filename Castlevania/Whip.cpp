//#include "Whip.h"
//#include "Simon.h"
//#include "StateMachine.h"
//
//
//void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	Width = tex->getWidth() / tex->_col;
//	Height = tex->getHeight() / tex->_row;
//	left = x - Width / 2;
//	top = y - Height / 2 + 16;
//	right = left + Width - 84 ;
//	bottom = top + Height - 35;
//}
//void CWhip::Render(CCamera* camera)
//{
//	if (!simon->isAttacking) return;
//	int d = 0;
//	int saniState = simon->GetAniState();
//	if (saniState == SIMON_ANI_DUCKING_ATTACKING_BEGIN || saniState == SIMON_ANI_DUCKING || saniState == SIMON_ANI_JUMPING)
//		d = SIMON_HEIGHT_ADJUST;
//	CAnimations::GetInstance()->Get(aniState)->Render(x, y + d, directionX);
//}
//
//int CWhip::IsCollidable()
//{
//	return (CAnimations::GetInstance()->Get(WHIP_ANI_ATTACKING_BEGIN)->GetCurrentFrame()== WHIP_ANI_ATTACKING_END);
//}
