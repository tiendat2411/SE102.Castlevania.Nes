#include "Sprites.h"
#include "Game.h"
#include "debug.h"
#include "Textures.h"


CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	//__instance->LoadResource();
	return __instance;
}
void CSprites::LoadResource(){
	CreateSpriteSheet(Type::SIMON);

	//CreateSpriteSheet(Type::MAP1);
	CreateSpriteSheet(Type::BRICK);

	CreateSpriteSheet(Type::FISHMAN);
	CreateSpriteSheet(Type::EAGLE);
	CreateSpriteSheet(Type::CANON);
	CreateSpriteSheet(Type::KNIGHT);
	CreateSpriteSheet(Type::AXEMAN);
	CreateSpriteSheet(Type::GHOST);
	CreateSpriteSheet(Type::FLEAMAN);
	CreateSpriteSheet(Type::LEOPARD);
	CreateSpriteSheet(Type::MEDUSA);
	CreateSpriteSheet(Type::RAVEN);
	CreateSpriteSheet(Type::SKELETON);
	CreateSpriteSheet(Type::BAT);
	CreateSpriteSheet(Type::ZOMBIE);
	CreateSpriteSheet(Type::WHIP);

	CreateSpriteSheet(Type::TILESET_LEVEL1);
	CreateSpriteSheet(Type::BLACKBOARD);


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
			CSprites::Add(_id,offset, x, y, spriteWidth - 1, spriteHeight - 1, tex);
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

