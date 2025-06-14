#include "Ground.h"



bool Ground::Initialize(LPCWSTR texturePath, float x, float y, int tag, int id)
{
	if (!GameObjectDem::Initialize(texturePath, x, y, tag, id))
		return false;
	return true;
}

Ground::Ground(int width, int height)
{
	this->width = width;
	this->height = height;
}


Ground::~Ground()
{
}

void Ground::Render(ViewPort* viewPort)
{
	D3DXVECTOR2 pos = this->position;

	for (int j = 0; j < height / 32; j++)
	{
		pos.y = this->position.y - 32 * j;
		for (int i = 0; i < width / 32; i++)
		{
			pos.x = this->position.x + 32 * i;
			sprite->Draw(position, viewPort);
		}
	}
}