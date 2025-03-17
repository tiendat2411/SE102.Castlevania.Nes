#pragma once
#include "GameObject.h"

	

class CFishMan:public CGameObject
{
private:

public:
	CFishMan(float x, float y);
	void Update(DWORD dt);
	void Render();
};

