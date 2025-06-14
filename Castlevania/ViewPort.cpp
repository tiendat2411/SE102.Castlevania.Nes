#include "ViewPort.h"


ViewPort::ViewPort(float x, float y)
{
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
}


ViewPort::~ViewPort()
{
}

D3DXVECTOR2 ViewPort::SetPositionInViewPort(D3DXVECTOR2 position)
{
	return D3DXVECTOR2(
		position.x - cameraPosition.x,          
		cameraPosition.y - position.y 
	);
}

void ViewPort::SetCameraPosition(float x, float y)
{
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
}

D3DXVECTOR2 ViewPort::GetCameraPosition()
{
	return this->cameraPosition;
}
