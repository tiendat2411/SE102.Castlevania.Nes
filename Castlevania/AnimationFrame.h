#pragma once

#include "SPRITE.h"

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	D3DXMATRIX matScaling;
public:
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite;  this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame* LPANIMATION_FRAME;

