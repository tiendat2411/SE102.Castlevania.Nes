#pragma once
#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__
#include <fstream>
#include <vector>

#include "QuadTree.h"
//#include "Item.h"
#include "SimonDemo.h"
#include "Graphics.h"
#include "ViewPort.h"

static int score;



class GameState
{
	float simonDeadTime = 1.5;
protected:

	ViewPort* viewPort;
	std::vector<GameObjectDem*>* listObject;
	bool changeState;
	float time;
	D3DXVECTOR2 simonCheckpoint;
	D3DXVECTOR2 cameraCheckpoint;
	bool canUseKeyboard;
	static SimonDemo* simon;

	float timeKillAll;
	bool choose;
	CGraphics* graphics;
public:
	int state;
	GameState() {}
	~GameState() {}

	virtual bool Initialize(CGraphics* graphics) = 0;
	virtual void Render() {};
	virtual void Update(float gameTime);
	virtual void DestroyAll() = 0;

	virtual bool GetChangingState() { return changeState; };
	virtual void SetChangingState(bool status) { changeState = status; }


	void CheckPointHandle(float gameTime, SimonDemo* simon, std::vector<GameObjectDem*>* list)
	{
		if (simon->IsColliderWithCheckPoint(gameTime, list))
		{
			simonCheckpoint = simon->GetPosition();
			cameraCheckpoint = viewPort->GetCameraPosition();
		}

		if (simon->GetPosition().y < viewPort->GetCameraPosition().y - GAME_HEIGHT) {
			simon->Reset(simonCheckpoint);
			viewPort->SetCameraPosition(cameraCheckpoint.x, cameraCheckpoint.y);
		}

		if (!simon->IsEnable())
		{
			{
				simon->Reset(simonCheckpoint);
				viewPort->SetCameraPosition(cameraCheckpoint.x, cameraCheckpoint.y);
			}
		}
	}
	virtual bool CameraFollowHandle(float gameTime) = 0;
};

#endif __GAMESTATE_H__
