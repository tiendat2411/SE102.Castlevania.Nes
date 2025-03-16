#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	directionX = DIRECTION_RIGHT;
	int directionY = -1;
	int aniState = SIMON_ANI_IDLE;
	isDeleted = false;
}

CGameObject::~CGameObject()
{

}