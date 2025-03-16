#include "Sprites.h"
#include "Game.h"
#include "debug.h"
#include "Textures.h"

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	__instance->LoadResource();
	return __instance;
}
void CSprites::LoadResource(){
	CreateSpriteSheet(Type::SIMON);
	CreateSpriteSheet(Type::BRICK);
}

void CSprites::CreateSpriteSheet(Type id)
{
	LPTEXTURE tex = CTextures::GetInstance()->Get(id);

	int x = 0, y = 0;
	int _id = static_cast<int>(id);
	int spriteWidth = tex->getWidth() / tex->_col;
	int spriteHeight = tex->getHeight() / tex->_row;
	

	for (int i = 0; i < tex->_row; ++i)
	{
		y = i * spriteHeight;
		for (int j = 0; j < tex->_col; ++j) {
			x = j * spriteWidth;
			int offset = i * tex->_col + j;
			CSprites::Add(_id,offset, x, y, spriteWidth, spriteHeight, tex);
		}
	}
}

void CSprites::Add(int id, int offset, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	LPSPRITE s = new CSprite(id + offset, left, top, right, bottom, tex);
	sprites[id + offset] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}
