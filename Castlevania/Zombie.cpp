#include "Zombie.h"
#include "Game.h"
#include "Animations.h"


void CZombie::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

}

void CZombie::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
	
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			directionX = -directionX;
		}
}


int CZombie::IsCollidable()
{
	return 1;
}
CZombie::CZombie(float x, float y, int directionX) : CGameObject(x, y) 
{ 
	this->directionX = directionX;
	aniState = ZOMBIE_ANI_BEGIN; 
	type = Type::SIMON;
	tex = CTextures::GetInstance()->Get(Type::ZOMBIE);
}

void CZombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	Width = tex->getWidth() / tex->_col;
	Height = tex->getHeight() / tex->_row;
	left = x - Width / 2;
	top = y - Height / 2;
	right = left + Width;
	bottom = top + Height;
}

void CZombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vx = ZOMBIE_SPEED_X * this->directionX;
	vy += ZOMBIE_GRAVITY * dt;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	int maxX = CGame::GetInstance()->GetBackBufferWidth(), maxY = CGame::GetInstance()->GetBackBufferHeight();
	// simple screen edge collision!!!
	if (vx > 0 && x > maxX) {
		x = maxX; directionX = -directionX;
	}
	if (vx < 0 && x < 0) {
		x = 0; directionX = -directionX;
	}
}
void CZombie::Render() {
	CAnimations::GetInstance()->Get(aniState)->Render(x, y , directionX);
}