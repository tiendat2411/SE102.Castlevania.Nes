#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Textures.h"
#include "AnimationFrame.h"


using namespace std;

class CAnimation
{
	int direction;
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; int direction = 1; }
	void Add(int spriteId, DWORD time = 0);
	void SetCurrentFrame(int curFrame = 0);
	void SetDefaultFrameTime(int startIdx,int endIdx,int time);
	void Render(float x, float y);
	void SetDirection(int direction ) { this->direction = direction; };
};

typedef CAnimation* LPANIMATION;