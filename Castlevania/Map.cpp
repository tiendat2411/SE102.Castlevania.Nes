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
	CCamera* cam = CCamera::GetInstance();
	float cx, cy,cw,ch;
	cam->GetCameraPos(cx, cy);
	cam->GetCameraWidthHeight(cw, ch);

	float startIndxRow, startIndxCol, endIndxRow, endIndxCol;
	int tileWidth = tilesTex->getWidth() / tilesTex->_col;
	int tileHeight = tilesTex->getHeight() / tilesTex->_row;

	startIndxRow = cy / tileHeight ;
	startIndxCol = cx / tileWidth ;
	endIndxRow = (cy + ch)/ tileHeight + 1;
	endIndxCol = (cx + cw )/ tileWidth + 1;

	
	for (int i = startIndxRow; i <= endIndxRow; i++)
		for (int j = startIndxCol; j <= endIndxCol; j++) {
			CSprites::GetInstance()->Get(static_cast<int>(lv) + TileMap[i][j])->Draw(cx + (j - startIndxCol+0.5f) * tileWidth, BOARD_HEIGHT	 +(i - startIndxRow) * tileHeight);
		}
	CSprites::GetInstance()->Get(static_cast<int>(Type::BLACKBOARD))->Draw(cx+ SCREEN_WIDTH/2 ,BOARD_HEIGHT/2);
}
