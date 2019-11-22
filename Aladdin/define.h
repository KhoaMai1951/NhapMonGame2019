#pragma once
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)

#define SCREEN_WIDTH 384  //320*1.2
#define SCREEN_HEIGHT 288
#define SCREEN_ACTUAL_WIDTH 367.2     //(320 - 14)*1.2    
#define SCREEN_ACTUAL_HEIGHT 242.4    //(240 - 38)*1.2
#define MAP_WIDTH 2271
#define MAP_HEIGHT 1138

#define CELL_SIZE 240

#define MAX_FRAME_RATE 120

//Object ID from text
#define GROUND0_ID "Ground0"
#define GROUND1_ID "Ground1"
#define PILLAR0_ID "pillar0"
#define PILLAR1_ID "pillar1"
#define PILLAR2_ID "pillar2"
#define PILLAR3_ID "pillar3"
#define EXIT_GATE_ID "exit_gate"
#define FRONT_CHAINS_ID "front_chains"
#define APPLE_ID "apple"

//Aladdin animation
enum AladdinAnimation
{
	ALADDIN = 100,
};

//Map animation

//Enemy animation
enum ItemAnimation
{
    ITEM = 400,
	ITEM_DESTROY = -401
};

//Texture ID
enum TEX_ID
{
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
    TEX_ITEM_DESTROY,

};