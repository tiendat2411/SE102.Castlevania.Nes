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
	__instance->LoadResource();
	return __instance;
}

void CTextures::LoadResource()
{
	Add(Type::SIMON, TEXTURE_PATH_SIMON1, 8, 3, 24);
	Add(Type::BRICK, TEXTURE_PATH_MISC, 1, 1, 1);

	if (textures[Type::SIMON]==nullptr) {
		DebugOut(L"[ERROR] testBrickSprite is NULL! ID_SPRITE_BRICK có thể chưa được thêm đúng\n");
	}
}

void CTextures::Add(Type type_id, LPCWSTR filePath,int col, int row, int totalSprites)
{
	textures[type_id] = CGame::GetInstance()->LoadTexture(filePath, col, row, totalSprites);
}

LPTEXTURE CTextures::Get(Type i)
{
	return textures[i];
}



