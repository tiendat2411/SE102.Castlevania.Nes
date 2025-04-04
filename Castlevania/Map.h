#pragma once
#include "Game.h"
#include "GameDefines.h"
#include "Camera.h"	
#include <vector>

class CMap
{
private:
	Type lv;
	LPTEXTURE tilesTex;
	int ColumnMap, RowMap;
	std::vector<std::vector<int>> TileMap;
public:
	CMap(Type level, LPTEXTURE tex)	: lv(level), tilesTex(tex), TileMap(500, std::vector<int>(500, 0)){}
	void LoadMapFromFile(LPCWSTR filename);
	void DrawMap();
	~CMap() {};
};

