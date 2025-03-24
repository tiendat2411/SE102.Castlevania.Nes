#pragma once
#include "Game.h"

class CCamera
{
private:
    static CCamera* __instance; 

    float cx, cy; 

public:
    CCamera() : cx(0), cy(0) {}

    static CCamera* GetInstance();
    void GetCameraPos(float& cx, float& cy) { cx = this->cx, cy = this->cy; }
    void Update(float targetX, float targetY);
    void Transform(float worldX, float worldY, float& screenX, float& screenY);
};
