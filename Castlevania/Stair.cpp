#include "Stair.h"

bool Stair::Initialize(LPCWSTR texturePath, float x, float y, int tag, int id)
{
	if (!GameObjectDem::Initialize(texturePath, x, y, tag, id))
		return false;
	return true;
}


Stair::Stair()
{
}


Stair::~Stair()
{
}
