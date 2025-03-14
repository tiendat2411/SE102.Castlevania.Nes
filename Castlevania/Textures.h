#pragma once
#include <unordered_map>
#include <d3dx10.h>
#include"GameDefines.h"
#include "Texture.h"

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures* __instance;

	unordered_map<Type, LPTEXTURE> textures;

public:
	CTextures();
	void Add(Type id, LPCWSTR filePath,int col = 1, int row = 1, int totalSprite = 1);
	void LoadResource();
	LPTEXTURE Get(Type i);

	static CTextures* GetInstance();
};