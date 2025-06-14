#pragma once
#ifndef GAME_H
#define GAME_H

#include "Graphics.h"
#include "SampleKeyEventHandler.h"
#include "Sprite.h"
#include "Simon.h"
#include "Collider.h"
#include "Zombie.h"
#include "UI.h"
#include "StateManager.h"
#include "GameTime.h"

class GameDemo
{
private:
	CGraphics* gDevice;
	ViewPort* viewPort;

	DWORD timeStart;
	DWORD timeNow;
	//float gameTime;
	GameTime* gameTime;
	//void TimeHandle();

	StateManager* stateManager;
public:
	GameDemo();
	~GameDemo();

	// game function
	bool Initialize(HWND hWnd, int width, int height);
	void Run(); 
	void Update(float _gameTime);
	void Draw();

};

#endif // !GAME_H