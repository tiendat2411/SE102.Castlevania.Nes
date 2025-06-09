#pragma once
#include "Game.h"
#include "debug.h"
#include "GameDefines.h"

class CCamera
{
private:
    static CCamera* __instance; 
	float width, height; // camera width and height
    float cx, cy; 
	float rangeX, rangeY; // range of camera movement on map

public:
    CCamera() : cx(0), cy(0) {
        width = CGame::GetInstance()->GetBackBufferWidth();
        height = CGame::GetInstance()->GetBackBufferHeight();
		rangeX = width;
		rangeY = height;
    }
	void SetRange(float rangeX, float rangeY) { 
        this->rangeX = rangeX, this->rangeY = rangeY;
    }
    void GetRange(float& rangeX, float& rangeY) { rangeX = this->rangeX; rangeY = this->rangeY; }
    static CCamera* GetInstance();
    void GetCameraPos(float& cx, float& cy) { cx = this->cx, cy = this->cy; }
	void GetCameraWidthHeight(float& w, float& h) { w = this->width, h = this->height; }
    void Update(float targetX, float targetY);
    void Transform(float screenX, float screenY, float& worldX, float& worldY);
};
