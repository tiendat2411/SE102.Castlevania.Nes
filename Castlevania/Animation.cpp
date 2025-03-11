#include "Animation.h"
#include "Sprites.h"







void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::SetCurrentFrame(int curFrame) {
	currentFrame = curFrame;
}
void CAnimation::SetDefaultFrameTime(int startIdx, int endIdx, int time) {
	for (int i = startIdx; i < endIdx; ++i) {
		frames[i]->time = time;
	}
}

void CAnimation::Render(float x, float y)
{
	ULONGLONG now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y);
}

//void CAnimation::Render(float x, float y)
//{
//	ULONGLONG now = GetTickCount64();
//	if (currentFrame == -1)
//	{
//		currentFrame = 0;
//		lastFrameTime = now;
//	}
//	else
//	{
//		DWORD t = frames[currentFrame]->GetTime();
//		if (now - lastFrameTime > t)
//		{
//			currentFrame++;
//			lastFrameTime = now;
//			if (currentFrame == frames.size()) currentFrame = 0;
//			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
//		}
//
//	}
//	if (direction > 0)
//		frames[currentFrame]->GetSprite()->Draw(x, y);
//	else
//		frames[currentFrame]->GetSprite()->FlipXDraw(x, y);
//}
//
