#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Textures.h"
#include "AnimationFrame.h"


using namespace std;

class CAnimation
{

	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1;  }
	void CreateNewAnimation(int startSpriteId, int EndSpriteId , DWORD time = 0);
	void Add(int spriteId, DWORD time = 0);
	void ReSetCurrentFrame();
	int GetCurrentFrame() { return currentFrame; }
	void SetDefaultFrameTime(int startIdx,int endIdx, int time);
	void Render(float x, float y,int direction = 1);
	BOOLEAN isAniFinished();
};

typedef CAnimation* LPANIMATION;