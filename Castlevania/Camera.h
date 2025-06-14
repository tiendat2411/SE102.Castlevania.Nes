#pragma once
#include "Game.h"
#include "debug.h"
#include "GameDefines.h"
#include <stdlib.h>
#include <cmath> 

class CCamera
{
private:
	static CCamera* __instance;

protected:
	D3DXVECTOR3 cameraPosition;

	float _xCam;
	float _yCam;

	float _xCamBackup;
	float _yCamBackup;
	float _boundaryLeftBackup;
	float _boundaryRightBackup;

	int _width;
	int _height;

	float _boundaryLeft; 
	float _boundaryRight; 

	float vx;
	DWORD dt;
	RECT *region;

	bool isAutoGoX; 
	float AutoGoX_Distance; 
	float AutoGoX_Backup_X; 

	bool isAllowFollowSimon;

public:
	CCamera() : _xCam(0), _yCam(0) {}
	CCamera(int w, int h);
	~CCamera();

	CCamera(float x, float y);

	D3DXVECTOR3 SetPositionInCamera(D3DXVECTOR3 position);

	void SetCameraPosition(float x, float y);

	D3DXVECTOR3 GetCameraPosition();

	static CCamera* GetInstance();
	void Transform(float screenX, float screenY, float& worldX, float& worldY);

	void Update(DWORD dt);

	D3DXVECTOR2 Transform(float, float);

	void SetPosition(float x, float y);

	float GetXCam();
	float GetYCam();
	int GetWidth();
	int GetHeight();

	bool checkObjectInCamera(float x, float y, float w, float h);
	void SetRegion(int left, int right, int top, int bottom)
	{
		region->left = _xCam + left;
		region->right = _xCam + right;
		region->top = _yCam + top;
		region->bottom = _yCam + bottom;
	}
	RECT* GetRegion() { return region; }

	bool AllowFollowSimon();
	void SetAllowFollowSimon(bool b);


	void SetAutoGoX(float Distance, float Speed); 
	void StopAutoGoX();
	bool GetIsAutoGoX();

	void SetBoundary(float left, float right); 
	float GetBoundaryRight();
	float GetBoundaryLeft();

	void SetPositionBackup(float X, float Y);
	void RestorePosition();

	void SetBoundaryBackup(float l, float r);
	void RestoreBoundary();
};

