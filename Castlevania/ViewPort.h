#pragma once
#include <D3DX10.h>

class ViewPort
{
private:
    D3DXVECTOR2 cameraPosition;  
    float width, height;      
    RECT* region;

public:
	ViewPort(float x, float y);
	~ViewPort();

	D3DXVECTOR2 SetPositionInViewPort(D3DXVECTOR2 position);

	void SetCameraPosition(float x, float y);

	D3DXVECTOR2 GetCameraPosition();
};