#pragma once
//#include "Enemy.h"
#include "ViewPort.h"

class Enemy;
class Candle : public Enemy
{
private:
	void InitAnim();
public:
	bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
	void Render(ViewPort* viewPort);
	void Update(float gameTime);
	Candle();
	~Candle();
};

