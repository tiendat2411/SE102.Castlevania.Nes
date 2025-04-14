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

public:
    CCamera() : cx(0), cy(0) {
        width = CGame::GetInstance()->GetBackBufferWidth();
        height = CGame::GetInstance()->GetBackBufferHeight();
    }

    static CCamera* GetInstance();
    void GetCameraPos(float& cx, float& cy) { cx = this->cx, cy = this->cy; }
	void GetCameraWidthHeight(float& w, float& h) { w = this->width, h = this->height; }
    void Update(float targetX, float targetY);
    void Transform(float screenX, float screenY, float& worldX, float& worldY);
};
