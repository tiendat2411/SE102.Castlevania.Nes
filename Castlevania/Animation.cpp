#include "Animation.h"
#include "Sprites.h"





void CAnimation::CreateNewAnimation(int startSpriteId, int EndSpriteId , DWORD time) {
	for (int i = startSpriteId; i <= EndSpriteId; ++i)
		Add(i, time);
}

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::ReSetCurrentFrame() {
	currentFrame = -1;
}
void CAnimation::SetDefaultFrameTime(int startIdx, int endIdx, int time) {
	for (int i = startIdx; i < endIdx; ++i) {
		frames[i]->time = time;
	}
}



void CAnimation::Render(float x, float y,int direction)
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
	if (direction < 0)
		frames[currentFrame]->GetSprite()->Draw(x, y);
	else
		frames[currentFrame]->GetSprite()->FlipXDraw(x, y);
}
BOOLEAN CAnimation::isAniFinished() {
	if (currentFrame != frames.size() - 1) return false;
	DWORD t = frames[currentFrame]->GetTime();
	ULONGLONG now = GetTickCount64();
	if( now - lastFrameTime < t)
		return false;
	return true;
}
