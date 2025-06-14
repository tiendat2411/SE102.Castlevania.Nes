#pragma once
#include <d3d10.h>
#include <d3dx10.h>
#include "ViewPort.h"
#include "define.h"
#include <string>
#include "Sprite.h"
#include <vector>
#include "SimonDemo.h"
#include "Textures.h"

class CSprite;
typedef CSprite* LPSPRITE;
class UI
{
private:
	ID3DX10Font* font;
	RECT rect;
	SimonDemo* simon;

	std::string information;

	std::vector<LPSPRITE>* simonHPList;
	std::vector<LPSPRITE>* enemyHPList;
	std::vector<LPSPRITE>* noHPList;

	LPSPRITE heart;
	LPSPRITE weapon;
	LPSPRITE black;
	LPSPRITE axe;
	LPSPRITE holyWater;
	LPSPRITE cross;
	LPSPRITE knife;
	LPSPRITE stopWatch;

	LPSPRITE upgrade1;
	LPSPRITE upgrade2;

	int simonHP;
	int bossHP;
	int uiHP;

	int score;
	int time;
	int item;
	int energy;
	int life;
	int stage;
	int subWeapon;

public:
	UI();
	~UI();
	bool Initialize(ID3D10Device* gDevice, SimonDemo* simon, int bossHP);
	void Update(int bossHP, int time, int life, int stage);
	void Render();
}; 
