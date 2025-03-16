#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	directionX = DIRECTION_POSITIVE;
	directionY = DIRECTION_POSITIVE;
	health = 1;
}