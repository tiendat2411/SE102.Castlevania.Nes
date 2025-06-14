 #include "Map.h"
#include "Sprites.h"
#include <fstream>
#include "Textures.h"

using namespace std;

void CMap::LoadMapFromFile(LPCWSTR filename) {	
	ifstream inp(filename, ios::in);
	inp >> RowMap >> ColumnMap >> ColumnTile >> RowTile >> TotalTiles >> HeightBoard;
	for (int i = 0; i < RowMap; i++)
		for (int j = 0; j < ColumnMap; j++)
			inp >> TileMap[i][j];
	inp.close();
}
void  CMap::DrawMap(ViewPort* viewPort) {
	CGame* g = CGame::GetInstance();

	float cx = viewPort->GetCameraPosition().x;
	float cy = viewPort->GetCameraPosition().y;
	
	float startIndxRow, startIndxCol, endIndxRow, endIndxCol;
	int tileWidth = tilesTex->getWidth() / tilesTex->_col;
	int tileHeight = tilesTex->getHeight() / tilesTex->_row;

	startIndxRow = cy / tileHeight ;
	startIndxCol = cx / tileWidth ;
	endIndxRow = (cy + g->GetBackBufferHeight()) / tileHeight + 1;
	endIndxCol = (cx + g->GetBackBufferWidth()) / tileWidth + 1;

	
	for (int i = startIndxRow; i <= endIndxRow; i++)
		for (int j = startIndxCol; j <= endIndxCol; j++) {
			CSprites::GetInstance()->Get(static_cast<int>(lv) + TileMap[i][j])->Draw(cx + (j - startIndxCol) * tileWidth, BOARD_HEIGHT + (i - startIndxRow + 0.5f) * tileHeight);
		}

}
