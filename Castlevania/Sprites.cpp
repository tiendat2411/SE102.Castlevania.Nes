#include "Sprites.h"
#include "Game.h"
#include "debug.h"
#include "Textures.h"

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

void CSprites::CreateSpriteSheet(int gameObjectId)
{
	LPTEXTURE tex = CTextures::GetInstance()->Get(gameObjectId);

	int x = 0, y = 0;
	int spriteWidth = tex->getWidth() / tex->_col;
	int spriteHeight = tex->getHeight() / tex->_row;
	

	for (int i = 0; i < tex->_totalSprites; ++i)
	{
		x = (i % tex->_col) * spriteWidth;
		y = (i % tex->_row) * spriteHeight;

		int spritesSize = CSprites::GetInstance()->GetSprites().size();
		CSprites::Add(spritesSize, x, y, spriteWidth, spriteHeight, tex);
	}
}

