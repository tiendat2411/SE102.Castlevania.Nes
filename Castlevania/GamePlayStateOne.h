#pragma once
#include "GameState.h"
#include "Map.h"
#include "SimonDemo.h"
#include "QuadTree.h"
#include "Ground.h"
//#include "LargeCandle.h"
#include "Zom.h"
#include "UI.h"
#include "CamGameObject.h"
//#include "Item.h"
//#include "WaterAnimation.h"

class CSprite;
typedef CSprite* LPSPRITE;

class GamePlayStateOne : public GameState
{
private:
	//Simon *simon;
	CMap* tileMap;

	LPSPRITE sprite;
	LPSPRITE castleSprite;

	GameObjectDem* ground;
	GameObjectDem* cameraObject;
	GameObjectDem* leftCamera;
	GameObjectDem* rightCamera;

	QuadTree* quadTree;
	UI* ui;

	std::vector<GameObjectDem*>* list;
	ID3D10Device* gDevice;
	//std::vector<Item*>* listItem;

public:
	GamePlayStateOne();
	~GamePlayStateOne();
	bool Initialize(CGraphics* graphics);
	void Render();
	void Update(float gameTime);
	void DestroyAll();

	bool GetChangingState();
	void SetChangingState(bool status);
	bool CameraFollowHandle(float gameTime) { return true; }
};
