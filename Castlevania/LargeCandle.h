#pragma once
#include "Enemy.h"
class LargeCandle : public Enemy
{
private:
	void InitAnim();
public:
	bool Initialize(LPCWSTR texturePath, float x, float y, int tag, int id);
	void Render(ViewPort* viewPort);
	void Update(float gameTime);
	LargeCandle();
	~LargeCandle();
};

