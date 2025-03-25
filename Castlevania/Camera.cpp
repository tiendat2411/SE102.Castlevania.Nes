#include "Camera.h"

CCamera* CCamera::__instance = nullptr;

void CCamera::Update(float targetX, float targetY)
{
    CGame* g = CGame::GetInstance();
    int screenWidth = g->GetBackBufferWidth();
    int screenHeight = g->GetBackBufferHeight();

    cx = targetX - screenWidth / 2;
    cy = 0;
    //cy = targetY - screenHeight / 2;

    if (cx < 0) cx = 0;
    if (cy < 0) cy = 0;
}

void CCamera::Transform(float screenX, float screenY, float& worldX, float& worldY)
{
    CGame* g = CGame::GetInstance();
    int screenHeight = g->GetBackBufferHeight();

    worldX = screenX - cx;
    worldY = screenHeight - (screenY - cy);
}

CCamera* CCamera::GetInstance()
{
    if (__instance == nullptr)
        __instance = new CCamera();
    return __instance;
}