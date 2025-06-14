#include "Camera.h"

CCamera* CCamera::__instance = nullptr;

CCamera* CCamera::GetInstance()
{
	if (__instance == nullptr)
		__instance = new CCamera();
	return __instance;
}

CCamera::CCamera(int w, int h)
{
	_width = w;
	_height = h;
	isAllowFollowSimon = true;
	isAutoGoX = false;

	_boundaryLeft = 0;
	_boundaryRight = 0;
	_xCamBackup = _yCamBackup = 0;
	SetBoundaryBackup(_boundaryLeft, _boundaryRight);
	vx = 0;

	SetRegion(0, w, 0, -h);
}

CCamera::~CCamera()
{
}

void CCamera::Update(DWORD dt)
{
	this->dt = dt;

	if (isAutoGoX)
	{
		float dx = vx * dt;
		_xCam += dx;
	}



	if (isAutoGoX == true)
	{
		if (abs(_xCam - AutoGoX_Backup_X) >= AutoGoX_Distance)
		{
			_xCam = _xCam - (abs(_xCam - AutoGoX_Backup_X) - AutoGoX_Distance);
			isAutoGoX = false;
		}
	}



	if (_xCam < _boundaryLeft)
		_xCam = _boundaryLeft;

	if (_xCam > _boundaryRight)
		_xCam = _boundaryRight;

}
D3DXVECTOR2 CCamera::Transform(float xWorld, float yWorld)
{
	return D3DXVECTOR2(xWorld - _xCam, yWorld - _yCam);
}

void CCamera::Transform(float screenX, float screenY, float& worldX, float& worldY)
{
	CGame* g = CGame::GetInstance();
	int screenHeight = g->GetBackBufferHeight();
	worldX = screenX - _xCam;
	worldY = screenHeight - (screenY - _yCam);
}

void CCamera::SetPosition(float x, float y)
{
	_xCam = x;
	_yCam = y;
}

float CCamera::GetXCam()
{
	return _xCam;
}

float CCamera::GetYCam()
{
	return _yCam;
}


int CCamera::GetWidth()
{
	return _width;
}

int CCamera::GetHeight()
{
	return _height;
}

bool CCamera::checkObjectInCamera(float x, float y, float w, float h)
{
	if (x + w < _xCam || _xCam + _width < x)
		return false;
	if (y + h < _yCam || _yCam + _height < y)
		return false;
	return true;
}

bool CCamera::AllowFollowSimon()
{
	return isAllowFollowSimon;
}

void CCamera::SetAllowFollowSimon(bool b)
{
	isAllowFollowSimon = b;
}

void CCamera::SetAutoGoX(float Distance, float Speed)
{
	if (isAutoGoX == true)
		return;
	vx = Speed;
	AutoGoX_Backup_X = _xCam;
	AutoGoX_Distance = Distance;
	isAutoGoX = true;
	isAllowFollowSimon = false;
}

void CCamera::StopAutoGoX()
{
	isAutoGoX = false;
}

bool CCamera::GetIsAutoGoX()
{
	return isAutoGoX;
}

void CCamera::SetBoundary(float left, float right)
{
	_boundaryLeft = left;
	_boundaryRight = right;
}

float CCamera::GetBoundaryRight()
{
	return _boundaryRight;
}

float CCamera::GetBoundaryLeft()
{
	return _boundaryLeft;
}

void CCamera::SetPositionBackup(float X, float Y)
{
	_xCamBackup = X;
	_yCamBackup = Y;
}

void CCamera::SetBoundaryBackup(float l, float r)
{
	_boundaryLeftBackup = l;
	_boundaryRightBackup = r;
}

void CCamera::RestoreBoundary()
{
	_boundaryLeft = _boundaryLeftBackup;
	_boundaryRight = _boundaryRightBackup;
}

void CCamera::RestorePosition()
{
	_xCam = _xCamBackup;
	_yCam = _yCamBackup;

	_boundaryLeft = _boundaryLeftBackup;
	_boundaryRight = _boundaryRightBackup;
}

CCamera::CCamera(float x, float y)
{
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
	this->cameraPosition.z = 0;
}


D3DXVECTOR3 CCamera::SetPositionInCamera(D3DXVECTOR3 position)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt); 

	mt._22 = -1.0f;
	mt._41 = -this->cameraPosition.x;
	mt._42 = this->cameraPosition.y;

	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	return D3DXVECTOR3(vp_pos.x, vp_pos.y, 0);
}

void CCamera::SetCameraPosition(float x, float y)
{
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
}

D3DXVECTOR3 CCamera::GetCameraPosition()
{
	return this->cameraPosition;
}
