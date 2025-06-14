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

	spriteWidth = (this->right - this->left + 1);
	spriteHeight = (this->bottom - this->top + 1);

	sprite.TexSize.x = spriteWidth / (float)tex->getWidth();
	sprite.TexSize.y = spriteHeight / (float)tex->getHeight();

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);
}

CSprite::CSprite(LPTEXTURE Texture, DWORD TimeAnimation)
{
	texture = Texture;
	currentFrame = 0;
	totalFrames = texture->_totalSprites - 1;
	//this->timeAnimation = TimeAnimation;
	//spriteHandler = Game::GetInstance()->GetSpriteHandler();
}


void CSprite::Draw(float x, float y)
{	
	CGame* g = CGame::GetInstance();
	CCamera* cam = CCamera::GetInstance();
	float worldX, worldY;
	cam->Transform(x, y, worldX, worldY);
	
	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, worldX, worldY, 0.1f);
	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

void CSprite::Draw( D3DXVECTOR2 position, ViewPort* viewPort)
{
	CGame* g = CGame::GetInstance();
	D3DXVECTOR2 world = viewPort->SetPositionInViewPort(position);

	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, world.x, world.y, 0.1f);
	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

void CSprite::Render(ViewPort* viewPort)
{
	CGame* g = CGame::GetInstance();
	D3DXVECTOR2 world = viewPort->SetPositionInViewPort(position);

	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, world.x, world.y, 0.1f);
	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

/*void CSprite::DrawFrame(float x, float y)
{
	RECT r = getRectFrame(currentFrame);
	D3DXVECTOR3 p(trunc(x), trunc(y), 0);
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
	CGame* game = CGame::GetInstance();
	game->GetSpriteHandler()->Draw(texture->getTexture(), &r, NULL, &p, color);
}*/

void CSprite::FlipXDraw(D3DXVECTOR2 position, ViewPort *viewPort)
{
	CGame* g = CGame::GetInstance();

	D3DXVECTOR2 world = viewPort->SetPositionInViewPort(position);

	D3DXMATRIX matTranslation, matFlipX ;
	D3DXMatrixTranslation(&matTranslation, world.x + sprite.TexSize.x, world.y, 0.1f);


	D3DXMatrixScaling(&matFlipX, -1, 1, 1);

	this->sprite.matWorld = (this->matScaling * matFlipX * matTranslation);
	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);

}

void CSprite::FlipXDraw(float x, float y)
{
	CGame* g = CGame::GetInstance();


	CCamera* cam = CCamera::GetInstance();

	float screenX, screenY;
	cam->Transform(x, y, screenX, screenY);

	D3DXMATRIX matTranslation, matFlipX;
	D3DXMatrixTranslation(&matTranslation, screenX + sprite.TexSize.x, screenY, 0.1f);


	D3DXMatrixScaling(&matFlipX, -1, 1, 1);

	this->sprite.matWorld = (this->matScaling * matFlipX * matTranslation);
	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);

}

RECT CSprite::getRectFrame(int id)
{
	RECT res;
	res.left = (id % texture->getCol()) * texture->getFrameWidth();
	res.top = (id / texture->getCol()) * texture->getFrameHeight();
	res.right = res.left + texture->getFrameWidth();
	res.bottom = res.top + texture->getFrameHeight();
	return res;
}

CSprite::CSprite(float x, float y)
{
	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	position.x = x;
	position.y = y;
	texture = NULL;
}

void CSprite::Draw()
{
	CGame* g = CGame::GetInstance();

	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, position.x, position.y, 0.1f);
	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

bool CSprite::Initialize(LPCWSTR texturePath, int id, int col, int row, int totalSprites)
{
	
	texture = CGame::GetInstance()->LoadTexture(texturePath, col, row, totalSprites);
	
	int x = 0, y = 0;
	int _id = static_cast<int>(id);
	int spriteWidth = texture->getWidth() / texture->_col;
	int spriteHeight = texture->getHeight() / texture->_row;


	for (int i = 0; i < texture->_row; ++i)
	{
		y = i * spriteHeight;
		for (int j = 0; j < texture->_col; ++j) {
			x = j * spriteWidth;
			int offset = i * texture->_col + j;
			CSprites::GetInstance()->Add(_id, offset, x, y, spriteWidth - 1, spriteHeight - 1, texture);
		}
	}

	return true;
}
