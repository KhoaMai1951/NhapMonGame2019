#pragma once
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_ACTUAL_HEIGHT 202
#define MAP_WIDTH 2271
#define MAP_HEIGHT 1138

#define CELL_SIZE 240

#define MAX_FRAME_RATE 120

//Object ID from text
#define GROUND0_ID "Ground0"
#define GOOMBA_ID "goomba_0"

//Aladdin animation
enum AladdinAnimation
{
	ALADDIN = 100,
};

//Map animation

//Enemy animation
enum GoombaAnimation
{
	GOOMBA_WALKING = 701
};

//Texture ID
enum TEX_ID
{
    ID_TEX_MARIO = -1111,
    ID_TEX_ENEMY = -2222,
    ID_TEX_MISC = -3333,
    ID_TEX_MAP = -4444,
	TEX_BBOX = -100,
	TEX_GROUND = -10,
	TEX_ALADDIN = 0,
	TEX_ALADDIN_LEFT = 1,
	TEX_MAP_DUNGEON = 10,
	TEX_DUNGEON_ENVIRONMENT = 11,
	TEX_MAP_BOSS = 20,
	TEX_APPLE = 30,
	TEX_GUARD = 40,
	TEX_GUARD_LEFT = 41,

};