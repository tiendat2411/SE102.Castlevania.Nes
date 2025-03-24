 #include "Map.h"
#include "Sprites.h"
#include <fstream>
#include "Textures.h"

using namespace std;

void CMap::LoadMapFromFile(LPCWSTR filename) {	
	ifstream inp(filename, ios::in);
	inp >> RowMap >> ColumnMap;
	for (int i = 0; i < RowMap; i++)
		for (int j = 0; j < ColumnMap; j++)
			inp >> TileMap[i][j];
	inp.close();
}
void  CMap::DrawMap() {
	CGame* g = CGame::GetInstance();
	CCamera* cam = CCamera::GetInstance();
	float cx, cy;
	cam->GetCameraPos(cx, cy);
	int startIndxRow, startIndxCol, endIndxRow, endIndxCol;
	int tileWidth = tilesTex->getWidth() / tilesTex->_col;
	int tileHeight = tilesTex->getHeight() / tilesTex->_row;

	startIndxRow = cy / tileHeight ;
	startIndxCol = cx / tileWidth ;
	endIndxRow = (cy + g->GetBackBufferHeight()) / tileHeight + 1;
	endIndxCol = (cx + g->GetBackBufferWidth()) / tileWidth + 1;

	
	for (int i = startIndxRow; i <= endIndxRow; i++)
		for (int j = startIndxCol; j <= endIndxCol; j++) {
			CSprites::GetInstance()->Get(static_cast<int>(lv) + TileMap[i][j])->Draw(cx + (j - startIndxCol) * tileWidth, g->GetBackBufferHeight()-384+64 + (i - startIndxRow) * tileHeight);
		}
	CSprites::GetInstance()->Get(static_cast<int>(Type::BLACKBOARD))->Draw(cx+320,47);
}
