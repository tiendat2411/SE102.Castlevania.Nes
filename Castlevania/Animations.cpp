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


	#pragma region CREATE_SIMON_ANIMATION

	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_IDLE, SIMON_ANI_IDLE);
	Add(SIMON_ANI_IDLE, ani);

	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_WALKING_BEGIN, SIMON_ANI_WALKING_END);
	Add(SIMON_ANI_WALKING_BEGIN, ani);


	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_DUCKING, SIMON_ANI_DUCKING);
	Add(SIMON_ANI_DUCKING, ani);

	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_HURTING, SIMON_ANI_HURTING);
	Add(SIMON_ANI_HURTING, ani);
	/******************ATTAKING********************/

	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_DUCKING_ATTACKING_BEGIN, SIMON_ANI_DUCKING_ATTACKING_END);
	Add(SIMON_ANI_DUCKING_ATTACKING_BEGIN, ani);


	ani = new CAnimation(100);
	ani->CreateNewAnimation(SIMON_ANI_STANDING_ATTACKING_BEGIN, SIMON_ANI_STANDING_ATTACKING_END);
	Add(SIMON_ANI_STANDING_ATTACKING_BEGIN, ani);

	ani = new CAnimation(100);
	ani->CreateNewAnimation(3000, 3000);
	Add(3000, ani);

	#pragma endregion 

	#pragma region CREATE_ENEMIES_ANIMATION

	ani = new CAnimation(500);
	ani->CreateNewAnimation(ZOMBIE_ANI_BEGIN,ZOMBIE_ANI_END);
	Add(ZOMBIE_ANI_BEGIN, ani);

	#pragma endregion

	#pragma region CREATE_WEAPON_ANIMATION
	ani = new CAnimation(100);
	ani->CreateNewAnimation(WHIP_ANI_ATTACKING_BEGIN, WHIP_ANI_ATTACKING_END);
	Add(WHIP_ANI_ATTACKING_BEGIN, ani);

	ani = new CAnimation(100);
	ani->CreateNewAnimation(AXE_ANI_ATTACKING_BEGIN, AXE_ANI_ATTACKING_END);
	Add(AXE_ANI_ATTACKING_BEGIN, ani);

	#pragma endregion

	



}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}