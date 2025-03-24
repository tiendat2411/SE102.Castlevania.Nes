#include "Sprite.h"

CSprite::CSprite(int id, int srcX, int srcY, int width, int height, LPTEXTURE tex)
{
	this->id = id;
	this->left = srcX;
	this->top = srcY;
	this->right = srcX + width;
	this->bottom = srcY + height;

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = this->left / (float)tex->getWidth();
	sprite.TexCoord.y = this->top / (float)tex->getHeight();

	int spriteWidth = (this->right - this->left + 1);
	int spriteHeight = (this->bottom - this->top + 1);

	sprite.TexSize.x = spriteWidth / (float)tex->getWidth();
	sprite.TexSize.y = spriteHeight / (float)tex->getHeight();

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);
}

void CSprite::Draw(float x, float y)
{	
	CGame* g = CGame::GetInstance();
	CCamera* cam = CCamera::GetInstance();
	float screenX, screenY;
	cam->Transform(x, y, screenX, screenY);
	
	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, screenX, screenY, 0.1f);
	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

void CSprite::FlipXDraw(float x, float y)
{
	CGame* g = CGame::GetInstance();
	CCamera* cam = CCamera::GetInstance();

	float screenX, screenY;
	cam->Transform(x, y, screenX, screenY);

	D3DXMATRIX matTranslation, matFlipX ;
	D3DXMatrixTranslation(&matTranslation, screenX + sprite.TexSize.x, screenY, 0.1f);
	D3DXMatrixScaling(&matFlipX, -1, 1, 1);

	this->sprite.matWorld = (this->matScaling * matFlipX * matTranslation);
	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);

}
