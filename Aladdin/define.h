#ifndef DEFINE_H
#define DEFINE_H
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)

#define SCREEN_WIDTH 384  //320*1.2
#define SCREEN_HEIGHT 288
#define SCREEN_ACTUAL_WIDTH 367.2     //(320 - 14)*1.2    
#define SCREEN_ACTUAL_HEIGHT 242.4    //(240 - 38)*1.2
#define MAP_WIDTH 2271
#define MAP_HEIGHT 1138
#define BOSS_MAP_WIDTH 1503
#define BOSS_MAP_HEIGHT 691

#define CELL_SIZE 240

#define MAX_FRAME_RATE 240

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

#define TILE_INDEX 900000
//Aladdin animation
enum AladdinAnimation
{

	ALADDIN = 100,
};

//Map animation

//Enemy animation
enum EnemyAnimation
{
	ENEMY_EXPLODE = 2000,
	GUARD0_IDLE_RIGHT = 2001,
	GUARD0_IDLE_LEFT = -2001,
	GUARD0_WALK_RIGHT = 2002,
	GUARD0_WALK_LEFT = -2002,
	GUARD0_ATTACK_RIGHT = 2003,
	GUARD0_ATTACK_LEFT = -2003,
	GUARD0_HURT_RIGHT = 2004,
	GUARD0_HURT_LEFT = -2004,

    GUARD1_IDLE_RIGHT = 2101,
    GUARD1_IDLE_LEFT = -2101,
    GUARD1_WALK_RIGHT = 2102,
    GUARD1_WALK_LEFT = -2102,
    GUARD1_TAUNT_RIGHT = 2103,
    GUARD1_TAUNT_LEFT = -2103,
    GUARD1_ATTACK1_RIGHT = 2104,
    GUARD1_ATTACK1_LEFT = -2104,
    GUARD1_ATTACK2_RIGHT = 2105,
    GUARD1_ATTACK2_LEFT = -2105,
    GUARD1_HURT_RIGHT = 2106,
    GUARD1_HURT_LEFT = -2106,

    SKELETON_ANI = 2201,
	BAT_IDLE = 2301,
	BAT_FLYING = 2302,

	BONE_FLYING = 2203,
};

enum DungeonAnimation
{
    ANI_STEP0 = 3101,
    ANI_STEP1 = 3102,
    ANI_SPIKE = 3201,
    ANI_SPIKE1 = 3202,
    ANI_WRECKING_BALL = 3301,
    ANI_WRECKING_BALL1 = 3302,
    ANI_PEDDLER_IDLE = 3501,
    ANI_PEDDLER_OPEN_SHOP = 3502,
};

enum ItemAnimation
{
    ITEM = 400,
    ITEM_DESTROY = -401,
    ANI_APPLE_FLYING_RIGHT = 4001,
    ANI_APPLE_FLYING_LEFT = 4002,
    ANI_THROW_APPLE_DESTROY = 4003,
    ANI_GENIE_IDLE = 4101,
    ANI_GENIE_IDLE2 = 4102,
    ANI_GENIE_EXPLODE = 4103,
    ANI_RUBY = 4201,
    ANI_SAVE_IDLE = 4301,
    ANI_SAVE_EATEN = 4302,
    ANI_LIFE = 4401,
};

enum SceneAnimation
{
    ANI_MAIN_MENU = 6001,
    ANI_LEVEL_COMPLETE = 6002,
    ANI_ALADDIN_LEVEL_COMPLETE = 6003,
    ANI_ABU_LEVEL_COMPLETE = 6004,
	ANI_BOSS_MAP = 6005,
};

enum HUDAnimation
{
	ANI_HEALTH_9 = 5009,
	ANI_HEALTH_8 = 5008,
	ANI_HEALTH_7 = 5007,
	ANI_HEALTH_6 = 5006,
	ANI_HEALTH_5 = 5005,
	ANI_HEALTH_4 = 5004,
	ANI_HEALTH_3 = 5003,
	ANI_HEALTH_2 = 5002,
	ANI_HEALTH_1 = 5001,
	ANI_CHARACTER= 5100,
	ANI_APPLE_HUD = 5201,
	ANI_RUBY_HUD = 5301,
	ANI_FACE_HUD = 5401,
    ANI_BLADE_POINTER_HUD = 5501,
};

//Texture ID
enum TEX_ID
{
    TEX_BBOX = -100,
    TEX_GROUND = -10,
    TEX_ALADDIN = 0,
    TEX_ALADDIN_LEFT = 1,
	TEX_ALADDIN_2 = 2,
	TEX_ALADDIN_2_LEFT = 3,
    TEX_MAP_DUNGEON = 10,
    TEX_DUNGEON_ENVIRONMENT = 11,
    TEX_MAP_BOSS = 20,
    TEX_APPLE = 30,
    TEX_GUARD = 40,
    TEX_GUARD_LEFT = 41,
    TEX_ITEM_DESTROY,
	TEX_TILESET_DUNGEON = 99,
	TEX_EXPLODE_SKELETON = 50,
	TEX_ITEM = 60,
	TEX_MAIN_MENU = 70,
	TEX_LEVEL_COMPLETE = 80,
	TEX_ABU = 90,
    TEX_ENEMY_EXPLODE = 100,
	TEX_BAT,
    TEX_GENIE_EXPLODE,
    TEX_EXIT_GATE,
    TEX_PEDDLER,
	TEX_BONE,
	TEX_CHARACTER,
    TEX_Extra_HUD,
};

#endif