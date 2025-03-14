#pragma once
#include <Windows.h>
#include <unordered_map>

#include <d3dx10.h>

#include "Texture.h"
#include "Sprite.h"
#include"GameDefines.h"

using namespace std;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites* __instance;
	unordered_map<int, LPSPRITE> sprites;
	void Add(int id, int offset, int left, int top, int right, int bottom, LPTEXTURE tex);
public:

	LPSPRITE Get(int id);
	unordered_map<int, LPSPRITE>& GetSprites() { return sprites; }
	void LoadResource();
	static CSprites* GetInstance();
	void CreateSpriteSheet(Type id);
};

