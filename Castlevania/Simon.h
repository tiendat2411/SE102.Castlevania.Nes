#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define SIMON_WALKING_SPEED		0.1f
#define SIMON_RUNNING_SPEED		0.2f

#define SIMON_ACCEL_WALK_X	0.0005f
#define SIMON_ACCEL_RUN_X	0.0007f

#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_RUN_SPEED_Y	0.6f

#define SIMON_GRAVITY			0.002f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200

#define SIMON_STATE_JUMP			300
#define SIMON_STATE_RELEASE_JUMP    301

#define SIMON_STATE_RUNNING_RIGHT	400
#define SIMON_STATE_RUNNING_LEFT	500

#define SIMON_STATE_SIT				600
#define SIMON_STATE_SIT_RELEASE		601


#pragma region ANIMATION_ID

#define ID_ANI_SIMON_IDLE_RIGHT 400
#define ID_ANI_SIMON_IDLE_LEFT 401

#define ID_ANI_SIMON_WALKING_RIGHT 500
#define ID_ANI_SIMON_WALKING_LEFT 501

#define ID_ANI_SIMON_RUNNING_RIGHT 600
#define ID_ANI_SIMON_RUNNING_LEFT 601

#define ID_ANI_SIMON_JUMP_WALK_RIGHT 700
#define ID_ANI_SIMON_JUMP_WALK_LEFT 701

#define ID_ANI_SIMON_JUMP_RUN_RIGHT 800
#define ID_ANI_SIMON_JUMP_RUN_LEFT 801

#define ID_ANI_SIMON_SIT_RIGHT 900
#define ID_ANI_SIMON_SIT_LEFT 901

#define ID_ANI_SIMON_BRACE_RIGHT 1000
#define ID_ANI_SIMON_BRACE_LEFT 1001

#pragma endregion




#define GROUND_Y 160.0f

#define SIMON_SIT_HEIGHT_ADJUST 4.0f

class CSimon : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
public:
	CSimon(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
	}
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
}; 
