#pragma once


#define SIMON_POSITION_DEFAULT  50.0f, 300.0f
#define DIRECTION_RIGHT 1
#define DIRECTION_DEFAULT 0
#define DIRECTION_LEFT -1

#pragma region SIMON_ANIMATION_


#define SIMON_DUCK_HEIGHT_ADJUST  10.0f // Kéo simon lên 18px sau khi ngồi rồi đứng dậy, tránh overlaping do BBOX bottom thu lại khi ngồi
#define SIMON_JUMP_HEIGHT_ADJUST 10.0f // Kéo simon lên 18px sau khi nhảy, tránh overlaping do BBOX bottom thu lại khi nhảy

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

//Ani Brick
#pragma endregion 


#define SIMON_GRAVITY 0.002f 

#define SIMON_WALKING_SPEED 0.1f 
#define SIMON_SPEED_ONSTAIR 0.09f 
#define SIMON_ACCEL_WALK_X	0.0005f
#define SIMON_JUMP_SPEED_Y 0.35f


#define SIMON_DEFAULT_HEALTH 16
#define SIMON_DEFAULT_HEARTCOLLECT 5
#define SIMON_DEFAULT_SCORE 0
#define SIMON_DEFAULT_LIVES 3


/*******TEXTURE_PATHS**********/

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_SIMON1 TEXTURES_DIR "\\simon.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\2.png"






/*******GAME OBJECT ID**********/
enum class Type {

	SIMON = 1000,
	// Enemy
	GHOST = 110,
	LEOPARD = 111,
	BAT = 112,
	FISHMEN = 113,
	VAMPIREBAT = 114,
	KNIGHT = 115,
	ZOOMBIE = 116,
	SKELETON = 117,
	CANON = 118,
	MEDUSA_HEAD = 119,
	FLEAMAN = 120,
	RAVEN = 121,


	//BOSS
	PHANTOMBAT = 210,
	MEDUSA = 211,
	MUMMYMAN = 212,
	FRANKENSTEIN = 213,
	DEATH = 214,
	DRACULAR = 215,
	COOKIE_MOSTER = 216,


	//BRICK
	BRICK = 3000,
};

enum class sType {
	SIMON_STATE_IDLE = 100,
	SIMON_STATE_JUMPING = 101,
	SIMON_STATE_DUCKING = 102,
	SIMON_STATE_WALKING = 103,
	SIMON_STATE_UPSTAIRS = 104,
	SIMON_STATE_DOWNSTAIRS = 105,
	DEFAULT_STATE = 0,

};