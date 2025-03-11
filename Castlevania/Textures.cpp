#include <Windows.h>

#include "debug.h"
#include "Game.h"
#include "textures.h"

CTextures* CTextures::__instance = NULL;

CTextures::CTextures()
{

}

CTextures* CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath,int col, int row, int totalSprites)
{
	textures[id] = CGame::GetInstance()->LoadTexture(filePath, col, row, totalSprites);
}

LPTEXTURE CTextures::Get(unsigned int i)
{
	return textures[i];
}



