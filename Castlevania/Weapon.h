#pragma once

#include "GameObject.h"

class CWeapon:public CGameObject
{
public:
	CWeapon(float x, float y) :CGameObject(x, y) {}
	~CWeapon() {};

};
typedef CWeapon* LPWEAPON;