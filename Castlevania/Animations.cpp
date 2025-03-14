#include "Animations.h"

CAnimations* CAnimations::__instance = NULL;

CAnimations* CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

void CAnimations::LoadResource() {
	CTextures* Textures = CTextures::GetInstance();

	LPANIMATION ani;
	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_IDLE, SIMON_ANI_IDLE);
	Add(SIMON_ANI_IDLE, ani);

	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_WALKING_BEGIN, SIMON_ANI_WALKING_END);
	Add(SIMON_ANI_WALKING_BEGIN, ani);


	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_DUCKING, SIMON_ANI_DUCKING);
	Add(SIMON_ANI_DUCKING, ani);

	/******************ATTAKING********************/

	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_DUCKING_ATTACKING_BEGIN, SIMON_ANI_DUCKING_ATTACKING_END);
	Add(SIMON_ANI_DUCKING_ATTACKING_BEGIN, ani);


	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_STANDING_ATTACKING_BEGIN, SIMON_ANI_STANDING_ATTACKING_END);
	Add(SIMON_ANI_STANDING_ATTACKING_BEGIN, ani);



}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}