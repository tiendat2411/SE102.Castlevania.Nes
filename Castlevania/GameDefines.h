﻿#pragma once


#define DIRECTION_POSITIVE 1	//right,down
#define DIRECTION_DEFAULT 0    //using current direction of obj
#define DIRECTION_NEGATIVE -1	//left,up

#pragma region TEXTURE_PATHS

#define TEXTURES_DIR L"textures"
#define ENEMYSTEX_DIR L"\\enemy"


#define TEXTURE_PATH_SIMON TEXTURES_DIR "\\simon.png"


#define TEXTURE_PATH_FISHMAN TEXTURES_DIR ENEMYSTEX_DIR  "\\FishMan.png"
#define TEXTURE_PATH_EAGLE TEXTURES_DIR ENEMYSTEX_DIR  "\\Eagle.png"
#define TEXTURE_PATH_CANON TEXTURES_DIR ENEMYSTEX_DIR "\\Dragon_Canon.png"
#define TEXTURE_PATH_KNIGHT TEXTURES_DIR ENEMYSTEX_DIR "\\Black_knight.png"
#define TEXTURE_PATH_AXEMAN TEXTURES_DIR ENEMYSTEX_DIR "\\Axe_Man.png"
#define TEXTURE_PATH_GHOST TEXTURES_DIR ENEMYSTEX_DIR "\\Ghost.png"
#define TEXTURE_PATH_FLEAMAN TEXTURES_DIR ENEMYSTEX_DIR "\\Fleaman.png"
#define TEXTURE_PATH_LEOPARD TEXTURES_DIR ENEMYSTEX_DIR "\\Leopard.png"
#define TEXTURE_PATH_MEDUSA TEXTURES_DIR ENEMYSTEX_DIR "\\Medusa.png"
#define TEXTURE_PATH_RAVEN TEXTURES_DIR ENEMYSTEX_DIR "\\Raven.png"
#define TEXTURE_PATH_SKELETON TEXTURES_DIR ENEMYSTEX_DIR "\\Skeleton.png"
#define TEXTURE_PATH_BAT TEXTURES_DIR ENEMYSTEX_DIR "\\Vampire_bat.png"
#define TEXTURE_PATH_ZOMBIE TEXTURES_DIR ENEMYSTEX_DIR "\\Zombie.png"

#pragma endregion

#pragma region SIMON_ANIMATION_

#define SIMON_HEIGHT_ADJUST  16.0f // adjust simon y position when sitting or jumping, avoid overlaping .

// aniID  = objectID + index of sprite in spriteSheet
#define SIMON_ANI_IDLE 1000

#define SIMON_ANI_WALKING_BEGIN 1001
#define SIMON_ANI_WALKING_END 1003

#define SIMON_ANI_JUMPING 1004
#define SIMON_ANI_DUCKING 1004


/**************ATTACKKING ANIMATION******************/

//Ani Duck Attack
#define SIMON_ANI_DUCKING_ATTACKING_BEGIN 1015
#define SIMON_ANI_DUCKING_ATTACKING_END 1017

//Ani Stand Attack
#define SIMON_ANI_STANDING_ATTACKING_BEGIN 1005
#define SIMON_ANI_STANDING_ATTACKING_END 1007

//Ani Climb down stairs Attack
#define SIMON_ANI_STAIR_DOWN_ATTACKING_BEGIN 1018
#define SIMON_ANI_STAIR_DOWN_ATTACKING_END 1020

//Ani Climb up stairs Attack
#define SIMON_ANI_STAIR_UP_ATTACKING_BEGIN 1021
#define SIMON_ANI_STAIR_UP_ATTACKING_END 1023

// Time Ani attack 
#define SIMON_TIME_ATTACKING_TRANS 120  //frame transition time when attacking

/*******************************************/

#define SIMON_ANI_HURTING 1008

#define SIMON_ANI_HIDE_FACE 1009


/*******NORMAL ON_STAIRS ANIMATION**********/

//Ani Climb down stairs
#define SIMON_ANI_STAIR_GO_DOWN_BEGIN 1010
#define SIMON_ANI_STAIR_GO_DOWN_END 1011

//Ani Climb down stairs
#define SIMON_ANI_STAIR_GO_UP_BEGIN 1012
#define SIMON_ANI_STAIR_GO_UP_END 1013

//Ani standing in stairs
#define SIMON_ANI_STAIR_STANDING_UP 1012
#define SIMON_ANI_STAIR_STANDING_DOWN 1010

/*******************************************/

#pragma endregion 

#pragma region ENEMIES_ANIMATION_
#define GHOST_ANI_BEGIN 1100
#define GHOST_ANI_END 1101

#define LEOPARD_ANI_IDLE 1110
#define LEOPARD_ANI_RUNING_BEGIN 1111
#define LEOPARD_ANI_RUNNING_END 1113

#define BAT_ANI_IDLE 1120
#define BAT_ANI_FLYING_BEGIN 1121
#define BAT_ANI_FLYING_END 1123

#define FISHMAN_ANI_ATTACKING 1130
#define FISHMAN_ANI_WALKING_BEGIN 1131
#define FISHMAN_ANI_WALKING_END 1132
#define FISHMAN_ANI_JUMPING 1133

#define AXEMAN_ANI_WALKING_BEGIN 1140
#define AXEMAN_ANI_WALKING_END 1141


#define KNIGHT_ANI_WALKING_BEGIN 1150
#define KNIGHT_ANI_WALKING_END 1153

#define ZOMBIE_ANI_BEGIN 1160
#define ZOMBIE_ANI_END 1161



#pragma endregion


/*******GAME OBJECT ID**********/
enum class Type {

	SIMON = 1000,

	// Enemy
	GHOST = 1100,
	LEOPARD = 1110,
	BAT = 1120,
	FISHMAN = 1130,
	AXEMAN = 1140,
	KNIGHT = 1150,
	ZOMBIE = 1160,
	SKELETON = 1170,
	CANON = 1180,
	MEDUSA_HEAD = 1190,
	FLEAMAN = 1200,
	RAVEN = 1210,
	EAGLE = 1220,
	


	//BOSS
	PHANTOMBAT = 2100,
	MEDUSA = 2110,
	MUMMYMAN = 2120,
	FRANKENSTEIN = 2130,
	DEATH = 2140,
	DRACULAR = 2150,
	COOKIE_MOSTER = 2160,


	//BRICK
	BRICK = 3000,
};

enum class sType {
	SIMON_STATE_IDLE = 100,
	SIMON_STATE_JUMPING = 101,
	SIMON_STATE_DUCKING = 102,
	SIMON_STATE_WALKING = 103,
	SIMON_STATE_ONSTAIRS = 104,
	SIMON_STATE_WALKING_ONSTAIRS = 105,
	DEFAULT_STATE = 0,

};