//#include "FishMan.h"
//#include "Animations.h"
//
//CFishMan::CFishMan(float x, float y) : CGameObject(x, y) {
//	aniState = FISHMAN_ANI_JUMPING;
//}
//void CFishMan::Update(DWORD dt) {
//
//	x += vx * dt;
//	y += vy * dt;
//
//	/*vx = ZOMBIE_SPEED_X * this->directionX;
//	vy += ZOMBIE_GRAVITY * dt;*/
//
//	int maxX = CGame::GetInstance()->GetBackBufferWidth(), maxY = CGame::GetInstance()->GetBackBufferHeight();
//	// simple screen edge collision!!!
//	if (vx > 0 && x > maxX) {
//		x = maxX; directionX = -directionX;
//	}
//	if (vx < 0 && x < 0) {
//		x = 0; directionX = -directionX;
//	}
//}
//void CFishMan::Render() {
//	CAnimations::GetInstance()->Get(aniState)->Render(x, y, directionX);
//}