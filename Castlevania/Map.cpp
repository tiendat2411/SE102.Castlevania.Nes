 #include "Map.h"
#include "Sprites.h"
#include <fstream>
#include "Textures.h"

using namespace std;

void CMap::LoadMapFromFile(LPCWSTR filename) {
	ifstream inp(filename, ios::in);
	if (!inp.is_open()) {
		DebugOut(L"[ERROR] Cannot open map file: %s", filename);
		return;
	}

	inp >> RowMap >> ColumnMap;

	TileMap = new int* [RowMap];

	for (int i = 0; i < RowMap; i++) {
		TileMap[i] = new int[ColumnMap];
		for (int j = 0; j < ColumnMap; j++) {
			inp >> TileMap[i][j];
			DebugOut(L"TileMap[%d][%d] = %d \n",i,j, TileMap[i][j]);
		}
	}

	inp.close();
}
void  CMap::DrawMap() {
	CCamera* cam = CCamera::GetInstance();
	float cx, cy,cw,ch;
	cam->GetCameraPos(cx, cy);
	cam->GetCameraWidthHeight(cw, ch);

	float startIndxRow, startIndxCol, endIndxRow, endIndxCol;
	int tileWidth = tilesTex->getWidth() / tilesTex->_col;
	int tileHeight = tilesTex->getHeight() / tilesTex->_row;

	startIndxRow = cy / tileHeight ;
	startIndxCol = cx / tileWidth ;
	endIndxRow = startIndxRow + ch/ tileHeight +1 ;
	endIndxCol = startIndxCol + cw / tileWidth  +1;

	if (endIndxCol >= ColumnMap) {
		endIndxCol = ColumnMap - 1;
	}
	if (endIndxRow >= RowMap)
		endIndxRow = RowMap - 1;
	
	for (int i = startIndxRow; i <= endIndxRow; i++)
		for (int j = startIndxCol; j <= endIndxCol; j++) {
			CSprites::GetInstance()->Get(static_cast<int>(lv) + TileMap[i][j])->Draw(cx + (j - startIndxCol+0.5f) * tileWidth, BOARD_HEIGHT	 +(i - startIndxRow) * tileHeight);
		}
	CSprites::GetInstance()->Get(static_cast<int>(Type::BLACKBOARD))->Draw(cx+ SCREEN_WIDTH/2 ,BOARD_HEIGHT/2);
}

