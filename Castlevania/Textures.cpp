#include <Windows.h>
#include "debug.h"
#include "Game.h"
#include "textures.h"
#include "Sprite.h"



CTextures* CTextures::__instance = NULL;

CTextures::CTextures()
{

}

CTextures* CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	//__instance->LoadResource();
	return __instance;
}


void CTextures::LoadResource()
{
	Add(Type::BRICK, TEXTURE_PATH_MISC, 1, 1, 1);

	Add(Type::SIMON, TEXTURE_PATH_SIMON, 8, 3, 24);
	Add(Type::FISHMAN, TEXTURE_PATH_FISHMAN, 4, 1, 4);
	Add(Type::EAGLE, TEXTURE_PATH_EAGLE, 2, 1, 2);
	Add(Type::CANON, TEXTURE_PATH_CANON, 1, 2, 2);
	Add(Type::KNIGHT, TEXTURE_PATH_KNIGHT, 4, 1, 4);
	Add(Type::AXEMAN, TEXTURE_PATH_AXEMAN, 2, 1, 2);
	Add(Type::GHOST, TEXTURE_PATH_GHOST, 2, 1, 2);
	Add(Type::FLEAMAN, TEXTURE_PATH_FLEAMAN, 2, 1, 2);
	Add(Type::LEOPARD, TEXTURE_PATH_LEOPARD, 4, 1, 4);
	Add(Type::MEDUSA, TEXTURE_PATH_MEDUSA, 2, 1, 2);
	Add(Type::RAVEN, TEXTURE_PATH_RAVEN, 4, 1, 4);
	Add(Type::SKELETON, TEXTURE_PATH_SKELETON, 4, 1, 4);
	Add(Type::BAT, TEXTURE_PATH_BAT, 4, 1, 4);
	Add(Type::ZOMBIE, TEXTURE_PATH_ZOMBIE, 2, 1, 2);
	Add(Type::WHIP, TEXTURE_PATH_WHIP, 3, 3, 9);
	Add(Type::AXE, TEXTURE_PATH_AXE, 4, 1, 4);
	
	Add(Type::TILESET_LEVEL1, TEXTURE_PATH_TILESET1, 8, 4, 32);
	Add(Type::BLACKBOARD, TEXTURE_PATH_BLACKBOARD);

	
}

void CTextures::Add(Type type_id, LPCWSTR filePath,int col, int row, int totalSprites)
{
	textures[type_id] = CGame::GetInstance()->LoadTexture(filePath, col, row, totalSprites);
}

LPTEXTURE CTextures::Get(Type i)
{
	return textures[i];
}



