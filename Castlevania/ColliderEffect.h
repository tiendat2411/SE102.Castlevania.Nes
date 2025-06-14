#pragma once
//#include "Sprite.h"

class CSprite;
typedef CSprite* LPSPRITE;
class ViewPort;
class CColliderEffect
{
private:
	LPSPRITE sprite;
	bool isVisible;
	float timeDelay;
public:
	CColliderEffect();
	~CColliderEffect();

	bool Initialize(LPCWSTR texturePath, float x, float y);
	void Render(ViewPort* viewPort);
	void Update(float gameTime);
	void SetPosition(float x, float y);
	void SetVisible(bool _isVisible) { isVisible = _isVisible; }
};

#pragma once
