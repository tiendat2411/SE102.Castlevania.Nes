#pragma once

#include "Texture.h"
#include "Game.h"
#include "Camera.h"
#include "Textures.h"
#include "Sprites.h"
#include "ViewPort.h"

class CSprite
{
	int id;
	int left;
	int top;
	int right;
	int bottom;

	int currentFrame;
	int totalFrames;
	
	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	

public:
	D3DXCOLOR color;
	int spriteWidth;
	int spriteHeight;
	int GetWidth() { return spriteWidth; }
	int GetHeight() { return spriteHeight; }
	D3DXMATRIX matScaling;
	D3DXVECTOR2 position;
	CSprite(int id, int srcX, int srcY, int width, int height, LPTEXTURE tex);
	CSprite(LPTEXTURE Texture, DWORD TimeAnimation);
	CSprite(float x, float y);
	void Draw(float x, float y);
	void Draw();
	void Render(ViewPort* viewPort);
	void Draw(D3DXVECTOR2 position, ViewPort *viewPort);
	void DrawFrame(float X, float Y);
	void FlipXDraw(float x, float y);
	void FlipXDraw(D3DXVECTOR2 position, ViewPort *viewPort);
	void SetPosition(int x, int y) { position.x = x; position.y = y; }
	void SetPosition(D3DXVECTOR2 _position) { position = _position; }
	RECT getRectFrame(int id);
	D3DXVECTOR2 GetPosition() { return position; }
	bool Initialize(LPCWSTR texturePath, int id, int col, int row, int totalSprites);
};

typedef CSprite* LPSPRITE;