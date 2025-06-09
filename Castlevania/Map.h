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
	int** TileMap;
public:
	CMap(Type level, LPTEXTURE tex)	: lv(level), tilesTex(tex){}
	void LoadMapFromFile(LPCWSTR filename);
	void DrawMap();
	float GetMapWidth() { return tilesTex->getWidth() / tilesTex->_col * ColumnMap; }
	float GetMapHeight() { return tilesTex->getHeight() / tilesTex->_row * RowMap; }
	~CMap() { 
		for (int i = 0; i < RowMap; ++i) 
			{
			delete[] TileMap[i];
		}
		delete[] TileMap;
	};
};

