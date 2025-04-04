#pragma once

#include "Texture.h"
#include "Game.h"
#include "Camera.h"

class CSprite
{
	int id;
	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite(int id, int srcX, int srcY, int width, int height, LPTEXTURE tex);
	void Draw(float x, float y);
	void FlipXDraw(float x, float y);
};

typedef CSprite* LPSPRITE;