#pragma once

#include "Animation.h"
#include "Sprite.h"

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	void LoadResource();
	LPANIMATION Get(int id);

	static CAnimations* GetInstance();
};