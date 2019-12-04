﻿#include "ResourceLoader.h"
#include "debug.h"

ResourceLoader* ResourceLoader::_instance = NULL;
ResourceLoader::ResourceLoader(void)
{
}

ResourceLoader::~ResourceLoader(void)
{
	//objects.clear();
	//objects.~vector();
	//map_vector.clear();
	//map_vector.~vector();
}

ResourceLoader* ResourceLoader::GetInstance()
{
	if (_instance == NULL)
		_instance = new ResourceLoader();
	return _instance;
}

void ResourceLoader::CreateAnimation()
{
    LoadSprite();
    LPANIMATION ani;
    CAnimations* animations = CAnimations::GetInstance();

#pragma region
	int aladdin_sprite_id = 10000;
	//idle right
	ani = new CAnimation(75);
	ani->Add(aladdin_sprite_id + 1);
	animations->Add(101, ani);

	//idle left
	ani = new CAnimation(75);
	ani->Add(-10001);
	animations->Add(-101, ani);

	//idle1
	ani = new CAnimation(100);
	/*for (int i = 11; i <= 17; i++)
	{
		ani->Add(100000 + i);
	}*/
	ani->Add(100011);
	ani->Add(100012, 750);
	ani->Add(100013);
	ani->Add(100014);
	ani->Add(100015);
	ani->Add(100016, 750);
	ani->Add(100017);
	animations->Add(1011, ani);

	//idle2
	ani = new CAnimation(100);
	for (int i = 17; i <= 31; i++)
	{
		ani->Add(100000 + i);
	}
	ani->Add(100032, 750);       //Sprite 15 of animation
	animations->Add(1012, ani);
	//idle3
	ani = new CAnimation(100);
	for (int i = 33; i <= 49; i++)
	{
		ani->Add(100000 + i);
	}
	ani->Add(100049);
	animations->Add(1013, ani);

	//running right
	ani = new CAnimation(75);
	for (int i = 2; i <= 13; i++)
	{
		ani->Add(aladdin_sprite_id + i);
	}
	animations->Add(102, ani);

	//running left
	ani = new CAnimation(75);
	for (int i = 2; i <= 13; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-102, ani);

	//jump right
	ani = new CAnimation(150);
	for (int i = 16; i <= 23; i++)  //Remove 14, 15 sprite
	{
		ani->Add(aladdin_sprite_id + i);
	}
	animations->Add(103, ani);

	//jump left
	ani = new CAnimation(150);
	for (int i = 16; i <= 23; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-103, ani);

	//run jump right  (//remove sprite 24, 31, 32)
	ani = new CAnimation(150);
	for (int i = 25; i <= 30; i++)
	{
		ani->Add(aladdin_sprite_id + i);
	}
	animations->Add(104, ani);

	//run jump left
	ani = new CAnimation(150);
	for (int i = 25; i <= 30; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-104, ani);

	//look up right
	ani = new CAnimation(100);
	for (int i = 33; i <= 35; i++)
	{
		ani->Add(aladdin_sprite_id + i);
	}
	animations->Add(105, ani);

	//look up left
	ani = new CAnimation(100);
	for (int i = 33; i <= 35; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-105, ani);

	//crouch right
	ani = new CAnimation(100);
	for (int i = 36; i <= 39; i++)
	{
		ani->Add(aladdin_sprite_id + i);
	}
	animations->Add(106, ani);

	//crouch left
	ani = new CAnimation(100);
	for (int i = 36; i <= 39; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-106, ani);

	//attack right
	ani = new CAnimation(100);
	for (int i = 40; i <= 44; i++)
	{
		ani->Add(aladdin_sprite_id + i);
	}
	animations->Add(107, ani);

	//attack left
	ani = new CAnimation(100);
	for (int i = 40; i <= 44; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-107, ani);

	//throw apple right standing
	ani = new CAnimation(100);
	for (int i = 445; i <= 450; i++)
	{
		ani->Add(aladdin_sprite_id + i);
	}
	animations->Add(108, ani);

	//throw apple left standing
	ani = new CAnimation(100);
	for (int i = 445; i <= 450; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-108, ani);

	//sit attack right
	ani = new CAnimation(100);
	for (int i = 46; i <= 51; i++)
	{
		ani->Add(aladdin_sprite_id + i);
	}
	animations->Add(109, ani);

	//sit attack left
	ani = new CAnimation(100);
	for (int i = 46; i <= 51; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-109, ani);

	//jump attack right
	ani = new CAnimation(100);
	for (int i = 557; i <= 562; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(110, ani);

	//jump attack left
	ani = new CAnimation(100);
	for (int i = 557; i <= 562; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-110, ani);

	//jump throw apple right
	ani = new CAnimation(100);
	for (int i = 58; i <= 62; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(111, ani);

	//jump throw apple left
	ani = new CAnimation(100);
	for (int i = 58; i <= 62; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-111, ani);

	//climb rope
	ani = new CAnimation(100);
	for (int i = 63; i <= 72; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(112, ani);

	//pushing right
	ani = new CAnimation(100);
	for (int i = 73; i <= 81; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(113, ani);

	//pushing left
	ani = new CAnimation(100);
	for (int i = 73; i <= 81; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-113, ani);

	//dead
	ani = new CAnimation(100);
	for (int i = 82; i <= 116; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(114, ani);

	//sit throw apple right
	ani = new CAnimation(100);
	for (int i = 52; i <= 56; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(115, ani);

	//sit throw apple left
	ani = new CAnimation(100);
	for (int i = 52; i <= 56; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(-115, ani);

	//climb throw left
	ani = new CAnimation(75);
	for (int i = 117; i <= 121; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(116, ani);

	//climb throw right
	ani = new CAnimation(75);
	for (int i = 117; i <= 121; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-116, ani);

	//climb attack left
	ani = new CAnimation(75);
	for (int i = 122; i <= 128; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(117, ani);

	//climb attack right
	ani = new CAnimation(75);
	for (int i = 122; i <= 128; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-117, ani);

	//climb jump
	ani = new CAnimation(75);
	for (int i = 129; i <= 137; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(118, ani);

	//running attack right
	ani = new CAnimation(75);
	for (int i = 138; i <= 143; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(119, ani);

	//running attack left
	ani = new CAnimation(75);
	for (int i = 138; i <= 143; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-119, ani);

	//running throw right
	ani = new CAnimation(75);
	for (int i = 144; i <= 149; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(120, ani);

	//running throw left
	ani = new CAnimation(75);
	for (int i = 144; i <= 149; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-120, ani);

	//hurt right
	ani = new CAnimation(75);
	for (int i = 150; i <= 155; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(121, ani);

	//hurt left
	ani = new CAnimation(75);
	for (int i = 150; i <= 155; i++)
	{
		ani->Add(-(aladdin_sprite_id + i));
	}
	animations->Add(-121, ani);

	//health
	ani = new CAnimation(75);
	for (int i = 156; i <= 188; i++)
	{
		ani->Add((aladdin_sprite_id + i));
	}
	animations->Add(122, ani);

#pragma endregion Aladdin

#pragma region
	int enemy_staff_sprite_id = 20000;

	//staff walk right
	ani = new CAnimation(75);
	for (int i = 1; i <= 8; i++)
	{
		ani->Add((enemy_staff_sprite_id + i));
	}
	animations->Add(123, ani);

	//staff walk left
	ani = new CAnimation(75);
	for (int i = 1; i <= 8; i++)
	{
		ani->Add(-(enemy_staff_sprite_id + i));
	}
	animations->Add(-123, ani);

	//staff attack right
	ani = new CAnimation(75);
	for (int i = 9; i <= 14; i++)
	{
		ani->Add((enemy_staff_sprite_id + i));
	}
	animations->Add(124, ani);

	//staff attack left
	ani = new CAnimation(75);
	for (int i = 9; i <= 14; i++)
	{
		ani->Add(-(enemy_staff_sprite_id + i));
	}
	animations->Add(-124, ani);

	//staff hurt right
	ani = new CAnimation(75);
	for (int i = 15; i <= 23; i++)
	{
		ani->Add((enemy_staff_sprite_id + i));
	}
	animations->Add(125, ani);

	//staff hurt left
	ani = new CAnimation(75);
	for (int i = 15; i <= 23; i++)
	{
		ani->Add(-(enemy_staff_sprite_id + i));
	}
	animations->Add(-125, ani);

	// enemy dead
	ani = new CAnimation(75);
	for (int i = 31; i <= 40; i++)
	{
		ani->Add((enemy_staff_sprite_id + i));
	}
	animations->Add(126, ani);

#pragma endregion Enemy Staff

#pragma region
	int enemy_blade_sprite_id = 21000;

	//blade walk right
	ani = new CAnimation(75);
	for (int i = 1; i <= 8; i++)
	{
		ani->Add((enemy_blade_sprite_id + i));
	}
	animations->Add(126, ani);

	//blade walk left
	ani = new CAnimation(75);
	for (int i = 1; i <= 8; i++)
	{
		ani->Add(-(enemy_blade_sprite_id + i));
	}
	animations->Add(-126, ani);

	//blade taunt right
	ani = new CAnimation(75);
	for (int i = 9; i <= 14; i++)
	{
		ani->Add((enemy_blade_sprite_id + i));
	}
	animations->Add(127, ani);

	//blade taunt left
	ani = new CAnimation(75);
	for (int i = 9; i <= 14; i++)
	{
		ani->Add(-(enemy_blade_sprite_id + i));
	}
	animations->Add(-127, ani);

	//blade attack 1 right
	ani = new CAnimation(75);
	for (int i = 15; i <= 19; i++)
	{
		ani->Add((enemy_blade_sprite_id + i));
	}
	animations->Add(128, ani);

	//blade attack 1 left
	ani = new CAnimation(75);
	for (int i = 15; i <= 19; i++)
	{
		ani->Add(-(enemy_blade_sprite_id + i));
	}
	animations->Add(-128, ani);

	//blade attack 2 right
	ani = new CAnimation(75);
	for (int i = 20; i <= 24; i++)
	{
		ani->Add((enemy_blade_sprite_id + i));
	}
	animations->Add(129, ani);

	//blade attack 2 left
	ani = new CAnimation(75);
	for (int i = 20; i <= 24; i++)
	{
		ani->Add(-(enemy_blade_sprite_id + i));
	}
	animations->Add(-129, ani);

	//blade hurt right
	ani = new CAnimation(75);
	for (int i = 25; i <= 30; i++)
	{
		ani->Add((enemy_blade_sprite_id + i));
	}
	animations->Add(130, ani);

	//blade hurt left
	ani = new CAnimation(75);
	for (int i = 25; i <= 30; i++)
	{
		ani->Add(-(enemy_blade_sprite_id + i));
	}
	animations->Add(-130, ani);
#pragma endregion Enemy Blade

#pragma region
	int explode_skeleton_sprite_id = 22000;

	//skeleton create
	ani = new CAnimation(75);
	for (int i = 0; i <= 6; i++)
	{
		ani->Add((explode_skeleton_sprite_id + i));
	}
	animations->Add(131, ani);

	//skeleton exploding
	ani = new CAnimation(75);
	for (int i = 7; i <= 19; i++)
	{
		ani->Add((explode_skeleton_sprite_id + i));
	}
	animations->Add(132, ani);
#pragma endregion Explode Skeleton

#pragma region
	int item_sprite_id = 50000;

	//Animation apple
	ani = new CAnimation(100);
	ani->Add(40001);
	animations->Add(401, ani);
	ani = new CAnimation(75); //item destroy of apple
	for (int i = 1; i <= 12; i++)
		ani->Add(-40000 - i);
	animations->Add(ITEM_DESTROY, ani);

	//genie
	ani = new CAnimation(75);
	for (int i = 1; i <= 4; i++)
	{
		ani->Add((item_sprite_id + i));
	}
	animations->Add(133, ani);

	//ruby
	ani = new CAnimation(75);
	for (int i = 5; i <= 13; i++)
	{
		ani->Add((item_sprite_id + i));
	}
	animations->Add(134, ani);

	//save idle
	ani = new CAnimation(75);
	ani->Add((item_sprite_id + 14));
	animations->Add(135, ani);

	//save eaten
	ani = new CAnimation(75);
	for (int i = 15; i <= 23; i++)
	{
		ani->Add((item_sprite_id + i));
	}
	animations->Add(136, ani);

	//life
	ani = new CAnimation(75);
	for (int i = 24; i <= 31; i++)
	{
		ani->Add((item_sprite_id + i));
	}
	animations->Add(137, ani);

	//face
	ani = new CAnimation(75);
	ani->Add((item_sprite_id + 32));
	animations->Add(138, ani);

#pragma endregion Items

#pragma region 
	int scene_sprite_id = 60000;

	//main menu
	ani = new CAnimation(75);
	ani->Add((item_sprite_id + 1));
	animations->Add(139, ani);

	//level complete
	ani = new CAnimation(75);
	ani->Add((item_sprite_id + 2));
	animations->Add(140, ani);

	//aladdin level complete
	ani = new CAnimation(75);
	for (int i = 3; i <= 10; i++)
	{
		ani->Add((item_sprite_id + i));
	}
	animations->Add(141, ani);

	//abu monkey level complete
	ani = new CAnimation(75);
	for (int i = 12; i <= 19; i++)
	{
		ani->Add((item_sprite_id + i));
	}
	animations->Add(142, ani);

#pragma endregion Scenes

#pragma region

	ani = new CAnimation(100);
	ani->Add(-30001);   //pillar0
	animations->Add(-301, ani);

	ani = new CAnimation(100);
	ani->Add(-30002);   //pillar1
	animations->Add(-302, ani);

	ani = new CAnimation(100);
	ani->Add(-30003);   //pillar2
	animations->Add(-303, ani);

	ani = new CAnimation(100);
	ani->Add(-30004);   //pillar3
	animations->Add(-304, ani);

	ani = new CAnimation(100);
	ani->Add(-30005);   //front_chains
	animations->Add(-305, ani);

#pragma endregion Dungeon environment

	//Animation ground
	ani = new CAnimation(100);
	ani->Add(30001);
	animations->Add(301, ani);
}

void ResourceLoader::LoadSprite()
{
    CTextures* textures = CTextures::GetInstance();

    textures->Add(TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
    textures->Add(TEX_MAP_DUNGEON, L"textures\\Sultans Dungeon_Back.png", D3DCOLOR_XRGB(255, 255, 255));
    textures->Add(TEX_DUNGEON_ENVIRONMENT, L"textures\\Sultans Dungeon_Object.png", D3DCOLOR_XRGB(163, 73, 164));
    textures->Add(TEX_ALADDIN, L"textures\\Aladdin.png", D3DCOLOR_XRGB(255, 0, 255));
    textures->Add(TEX_ALADDIN_LEFT, L"textures\\Aladdin_left.png", D3DCOLOR_XRGB(255, 0, 255));
    textures->Add(TEX_GUARD, L"textures\\Guards.png", D3DCOLOR_XRGB(255, 0, 255));
    textures->Add(TEX_GUARD_LEFT, L"textures\\Guards_left.png", D3DCOLOR_XRGB(120, 193, 152));
    textures->Add(TEX_APPLE, L"textures\\Apple.png", D3DCOLOR_XRGB(120, 193, 152));
    textures->Add(TEX_GROUND, L"textures\\Ground.png", D3DCOLOR_XRGB(255, 255, 255));
    textures->Add(TEX_ITEM_DESTROY, L"textures\\Items_destroy.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(TEX_ITEM, L"textures\\Items.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(TEX_ALADDIN_2, L"textures\\Aladdin2.png", D3DCOLOR_XRGB(105, 148, 190));
	textures->Add(TEX_ALADDIN_2_LEFT, L"textures\\Aladdin2_left.png", D3DCOLOR_XRGB(105, 148, 190));
	textures->Add(TEX_EXPLODE_SKELETON, L"textures\\Explode Skeleton.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(TEX_MAIN_MENU, L"textures\\Menu.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(TEX_LEVEL_COMPLETE, L"textures\\LevelComplete.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(TEX_ABU, L"textures\\Abu.png", D3DCOLOR_XRGB(255, 255, 255));
    textures->Add(TEX_ENEMY_EXPLODE, L"textures\\Enemy_exlode.png", D3DCOLOR_XRGB(255, 255, 255));


    CSprites* sprites = CSprites::GetInstance();

#pragma region
    LPDIRECT3DTEXTURE9 texAladdin = textures->Get(TEX_ALADDIN);
    LPDIRECT3DTEXTURE9 texAladdin_Left = textures->Get(TEX_ALADDIN_LEFT);
	LPDIRECT3DTEXTURE9 texAladdin2 = textures->Get(TEX_ALADDIN_2);
	LPDIRECT3DTEXTURE9 texAladdin2_Left = textures->Get(TEX_ALADDIN_2_LEFT);

	sprites->Add(100011, 47, 11, 88, 58, texAladdin);		// idle1
	sprites->Add(100012, 95, 6, 135, 58, texAladdin);
	sprites->Add(100013, 143, 3, 187, 58, texAladdin);
	sprites->Add(100014, 197, 6, 238, 57, texAladdin);
	sprites->Add(100015, 250, 5, 292, 56, texAladdin);
	sprites->Add(100016, 303, 2, 347, 55, texAladdin);
	sprites->Add(100017, 197, 6, 238, 57, texAladdin);      //start of idle2

	sprites->Add(100018, 6, 83, 46, 135, texAladdin);		// idle2
	sprites->Add(100019, 51, 81, 112, 134, texAladdin);
	sprites->Add(100020, 116, 80, 178, 134, texAladdin);
	sprites->Add(100021, 180, 81, 221, 134, texAladdin);
	sprites->Add(100022, 228, 81, 267, 134, texAladdin);
	sprites->Add(100023, 275, 81, 311, 134, texAladdin);
	sprites->Add(100024, 319, 81, 359, 134, texAladdin);
	sprites->Add(100025, 366, 79, 407, 134, texAladdin);
	sprites->Add(100026, 417, 61, 460, 134, texAladdin);
	sprites->Add(100027, 465, 57, 507, 134, texAladdin);
	sprites->Add(100028, 516, 63, 558, 134, texAladdin);
	sprites->Add(100029, 568, 72, 610, 134, texAladdin);
	sprites->Add(100030, 619, 80, 660, 134, texAladdin);
	sprites->Add(100031, 668, 80, 708, 134, texAladdin);
	sprites->Add(100032, 715, 81, 754, 134, texAladdin);
	sprites->Add(100033, 3, 165, 39, 218, texAladdin);      //idle3
	sprites->Add(100034, 46, 165, 86, 218, texAladdin);
	sprites->Add(100035, 91, 163, 132, 218, texAladdin);
	sprites->Add(100036, 140, 155, 178, 218, texAladdin);
	sprites->Add(100037, 188, 151, 229, 218, texAladdin);
	sprites->Add(100038, 238, 159, 280, 218, texAladdin);
	sprites->Add(100039, 287, 168, 325, 218, texAladdin);
	sprites->Add(100040, 334, 168, 373, 218, texAladdin);
	sprites->Add(100041, 378, 168, 417, 218, texAladdin);
	sprites->Add(100042, 425, 156, 463, 218, texAladdin);
	sprites->Add(100043, 472, 150, 510, 218, texAladdin);
	sprites->Add(100044, 519, 143, 555, 218, texAladdin);
	sprites->Add(100045, 568, 138, 607, 218, texAladdin);
	sprites->Add(100046, 615, 155, 657, 218, texAladdin);
	sprites->Add(100047, 666, 163, 707, 218, texAladdin);
	sprites->Add(100048, 715, 163, 755, 218, texAladdin);
	sprites->Add(100049, 762, 164, 801, 218, texAladdin);

	sprites->Add(10001, 14, 1225, 54, 1273, texAladdin);		// idle right
	sprites->Add(10002, 66, 1222, 109, 1273, texAladdin);       //running right
	sprites->Add(10003, 120, 1220, 161, 1273, texAladdin);
	sprites->Add(10004, 171, 1216, 212, 1273, texAladdin);
	sprites->Add(10005, 220, 1216, 272, 1273, texAladdin);
	sprites->Add(10006, 279, 1219, 325, 1273, texAladdin);
	sprites->Add(10007, 334, 1215, 376, 1273, texAladdin);
	sprites->Add(10008, 386, 1221, 427, 1273, texAladdin);
	sprites->Add(10009, 440, 1219, 475, 1273, texAladdin);
	sprites->Add(10010, 488, 1216, 537, 1273, texAladdin);
	sprites->Add(10011, 547, 1215, 602, 1273, texAladdin);
	sprites->Add(10012, 611, 1219, 666, 1273, texAladdin);
	sprites->Add(10013, 679, 1218, 723, 1273, texAladdin);

	sprites->Add(-10001, 1067, 1225, 1107, 1273, texAladdin_Left); //idle left
	sprites->Add(-10002, 1012, 1222, 1055, 1273, texAladdin_Left); //running left
	sprites->Add(-10003, 960, 1220, 1001, 1273, texAladdin_Left);
	sprites->Add(-10004, 909, 1216, 950, 1273, texAladdin_Left);
	sprites->Add(-10005, 849, 1216, 901, 1273, texAladdin_Left);
	sprites->Add(-10006, 796, 1219, 842, 1273, texAladdin_Left);
	sprites->Add(-10007, 745, 1215, 787, 1273, texAladdin_Left);
	sprites->Add(-10008, 694, 1221, 735, 1273, texAladdin_Left);
	sprites->Add(-10009, 646, 1219, 681, 1273, texAladdin_Left);
	sprites->Add(-10010, 584, 1216, 633, 1273, texAladdin_Left);
	sprites->Add(-10011, 519, 1215, 574, 1273, texAladdin_Left);
	sprites->Add(-10012, 455, 1219, 510, 1273, texAladdin_Left);
	sprites->Add(-10013, 398, 1218, 442, 1273, texAladdin_Left);

	sprites->Add(10014, 8, 846, 67, 889, texAladdin); //jump right
	sprites->Add(10015, 75, 828, 127, 890, texAladdin);
	sprites->Add(10016, 137, 829, 191, 890, texAladdin);
	sprites->Add(10017, 203, 824, 257, 893, texAladdin);
	sprites->Add(10018, 269, 820, 320, 894, texAladdin);
	sprites->Add(10019, 336, 829, 374, 895, texAladdin);
	sprites->Add(10020, 390, 818, 425, 897, texAladdin);
	sprites->Add(10021, 448, 808, 482, 901, texAladdin);
	sprites->Add(10022, 504, 810, 538, 903, texAladdin);
	sprites->Add(10023, 564, 812, 598, 905, texAladdin);

	sprites->Add(-10014, 1054, 846, 1113, 889, texAladdin_Left);//jump left
	sprites->Add(-10015, 994, 828, 1046, 890, texAladdin_Left);
	sprites->Add(-10016, 930, 829, 984, 890, texAladdin_Left);
	sprites->Add(-10017, 864, 824, 918, 893, texAladdin_Left);
	sprites->Add(-10018, 801, 820, 852, 894, texAladdin_Left);
	sprites->Add(-10019, 747, 829, 785, 895, texAladdin_Left);
	sprites->Add(-10020, 696, 818, 731, 897, texAladdin_Left);
	sprites->Add(-10021, 639, 808, 673, 901, texAladdin_Left);
	sprites->Add(-10022, 583, 810, 617, 903, texAladdin_Left);
	sprites->Add(-10023, 523, 812, 557, 905, texAladdin_Left);

	sprites->Add(10024, 10, 705, 51, 747, texAladdin); //run jump right
	sprites->Add(10025, 66, 683, 111, 759, texAladdin);
	sprites->Add(10026, 124, 686, 181, 743, texAladdin);
	sprites->Add(10027, 199, 698, 257, 740, texAladdin);
	sprites->Add(10028, 273, 696, 334, 744, texAladdin);
	sprites->Add(10029, 350, 692, 408, 745, texAladdin);
	sprites->Add(10030, 419, 688, 472, 746, texAladdin);
	sprites->Add(10031, 491, 680, 541, 765, texAladdin);
	sprites->Add(10032, 560, 719, 619, 763, texAladdin);

	sprites->Add(-10024, 1070, 705, 1111, 747, texAladdin_Left); //run jump left
	sprites->Add(-10025, 1010, 683, 1055, 759, texAladdin_Left);
	sprites->Add(-10026, 940, 686, 997, 743, texAladdin_Left);
	sprites->Add(-10027, 864, 698, 922, 740, texAladdin_Left);
	sprites->Add(-10028, 787, 696, 848, 744, texAladdin_Left);
	sprites->Add(-10029, 713, 692, 771, 745, texAladdin_Left);
	sprites->Add(-10030, 649, 688, 702, 746, texAladdin_Left);
	sprites->Add(-10031, 580, 680, 630, 765, texAladdin_Left);
	sprites->Add(-10032, 502, 719, 561, 763, texAladdin_Left);

	sprites->Add(10033, 11, 496, 50, 549, texAladdin);        //look up right
	sprites->Add(10034, 59, 490, 104, 549, texAladdin);
	sprites->Add(10035, 111, 491, 160, 549, texAladdin);

	sprites->Add(-10033, 1071, 496, 1110, 549, texAladdin_Left);  //look up left
	sprites->Add(-10034, 1017, 490, 1062, 549, texAladdin_Left);
	sprites->Add(-10035, 961, 491, 1010, 549, texAladdin_Left);

	sprites->Add(10036, 205, 500, 247, 549, texAladdin);       //crouch right
	sprites->Add(10037, 258, 509, 306, 549, texAladdin);
	sprites->Add(10038, 315, 519, 369, 549, texAladdin);
	sprites->Add(10039, 378, 516, 431, 551, texAladdin);

	sprites->Add(-10036, 874, 500, 916, 549, texAladdin_Left);  //crouch left
	sprites->Add(-10037, 815, 509, 863, 549, texAladdin_Left);
	sprites->Add(-10038, 752, 519, 806, 549, texAladdin_Left);
	sprites->Add(-10039, 690, 516, 743, 551, texAladdin_Left);

	//attack (standing, no wall) - dòng 5
	sprites->Add(10040, 5, 337, 50, 388, texAladdin);
	sprites->Add(10041, 54, 326, 105, 388, texAladdin);
	sprites->Add(10042, 115, 314, 160, 388, texAladdin);
	sprites->Add(10043, 171, 319, 253, 388, texAladdin);
	sprites->Add(10044, 260, 335, 311, 388, texAladdin);
	//attack left (standing, no wall) - dòng 5
	sprites->Add(-10040, 1071, 337, 1116, 388, texAladdin_Left);
	sprites->Add(-10041, 1016, 326, 1067, 388, texAladdin_Left);
	sprites->Add(-10042, 961, 314, 1006, 388, texAladdin_Left);
	sprites->Add(-10043, 868, 319, 950, 388, texAladdin_Left);
	sprites->Add(-10044, 810, 335, 861, 388, texAladdin_Left);
	//throw apple (standing) - dòng 4
	sprites->Add(10445, 7, 235, 50, 291, texAladdin);
	sprites->Add(10446, 57, 232, 98, 291, texAladdin);
	sprites->Add(10447, 109, 233, 147, 291, texAladdin);
	sprites->Add(10448, 163, 231, 209, 291, texAladdin);
	sprites->Add(10449, 221, 233, 258, 291, texAladdin);
	sprites->Add(10450, 268, 239, 307, 291, texAladdin);
	//throw apple left(standing) - dòng 4
	sprites->Add(-10445, 1071, 235, 1114, 291, texAladdin_Left);
	sprites->Add(-10446, 1023, 232, 1064, 291, texAladdin_Left);
	sprites->Add(-10447, 974, 233, 1012, 291, texAladdin_Left);
	sprites->Add(-10448, 912, 231, 958, 291, texAladdin_Left);
	sprites->Add(-10449, 863, 233, 900, 291, texAladdin_Left);
	sprites->Add(-10450, 814, 239, 853, 291, texAladdin_Left);
	//attack (sitting) - dòng 9
	sprites->Add(10046, 9, 640, 56, 673, texAladdin);
	sprites->Add(10047, 64, 642, 109, 673, texAladdin);
	sprites->Add(10048, 115, 640, 186, 673, texAladdin);
	sprites->Add(10049, 193, 639, 285, 673, texAladdin);
	sprites->Add(10050, 298, 640, 382, 673, texAladdin);
	sprites->Add(10051, 392, 640, 463, 673, texAladdin);
	sprites->Add(10051, 475, 642, 520, 673, texAladdin);
	//attack (sitting) left - dòng 9
	sprites->Add(-10046, 1065, 640, 1112, 673, texAladdin_Left);
	sprites->Add(-10047, 1012, 642, 1057, 673, texAladdin_Left);
	sprites->Add(-10048, 935, 640, 1006, 673, texAladdin_Left);
	sprites->Add(-10049, 836, 639, 928, 673, texAladdin_Left);
	sprites->Add(-10050, 739, 640, 823, 673, texAladdin_Left);
	sprites->Add(-10051, 658, 640, 729, 673, texAladdin_Left);
	sprites->Add(-10051, 601, 642, 646, 673, texAladdin_Left);
	//throw apple (sitting) - dòng 8
	sprites->Add(10052, 9, 571, 46, 615, texAladdin);
	sprites->Add(10053, 58, 567, 95, 615, texAladdin);
	sprites->Add(10054, 107, 571, 157, 619, texAladdin);
	sprites->Add(10055, 164, 578, 246, 615, texAladdin);
	sprites->Add(10056, 256, 579, 313, 616, texAladdin);
	//throw apple (sitting) left - dòng 8
	sprites->Add(-10052, 1075, 571, 1112, 615, texAladdin_Left);
	sprites->Add(-10053, 1026, 567, 1063, 615, texAladdin_Left);
	sprites->Add(-10054, 964, 571, 1014, 619, texAladdin_Left);
	sprites->Add(-10055, 875, 578, 957, 615, texAladdin_Left);
	sprites->Add(-10056, 808, 579, 865, 616, texAladdin_Left);
	//attack (jumping) - dòng 14
	sprites->Add(10557, 13, 1077, 65, 1131, texAladdin);
	sprites->Add(10558, 75, 1075, 125, 1127, texAladdin);
	sprites->Add(10559, 140, 1067, 187, 1133, texAladdin);
	sprites->Add(10560, 199, 1078, 251, 1134, texAladdin);
	sprites->Add(10561, 266, 1070, 349, 1130, texAladdin);
	sprites->Add(10562, 361, 1087, 408, 1142, texAladdin);
	//attack (jumping) left - dòng 14
	sprites->Add(-10557, 1056, 1077, 1108, 1131, texAladdin_Left);
	sprites->Add(-10558, 996, 1075, 1046, 1127, texAladdin_Left);
	sprites->Add(-10559, 934, 1067, 981, 1133, texAladdin_Left);
	sprites->Add(-10560, 870, 1078, 922, 1134, texAladdin_Left);
	sprites->Add(-10561, 772, 1070, 855, 1130, texAladdin_Left);
	sprites->Add(-10562, 701, 1087, 760, 1142, texAladdin_Left);
	//throw apple (jumping) - dòng 13
	sprites->Add(10058, 19, 1005, 68, 1060, texAladdin);
	sprites->Add(10059, 77, 1007, 120, 1059, texAladdin);
	sprites->Add(10060, 132, 1008, 171, 1061, texAladdin);
	sprites->Add(10061, 185, 1008, 237, 1061, texAladdin);
	sprites->Add(10062, 253, 1012, 293, 1064, texAladdin);
	//throw apple (jumping) left - dòng 13
	sprites->Add(-10058, 1053, 1005, 1102, 1060, texAladdin_Left);
	sprites->Add(-10059, 1001, 1007, 1044, 1059, texAladdin_Left);
	sprites->Add(-10060, 950, 1008, 989, 1061, texAladdin_Left);
	sprites->Add(-10061, 884, 1008, 936, 1061, texAladdin_Left);
	sprites->Add(-10062, 828, 1012, 868, 1064, texAladdin_Left);
	//leo dây (ko có left-right)
	sprites->Add(10063, 11, 1362, 40, 1448, texAladdin);
	sprites->Add(10064, 53, 1361, 81, 1450, texAladdin);
	sprites->Add(10065, 94, 1374, 122, 1448, texAladdin);
	sprites->Add(10066, 133, 1377, 175, 1439, texAladdin);
	sprites->Add(10067, 186, 1363, 217, 1439, texAladdin);
	sprites->Add(10068, 231, 1358, 260, 1444, texAladdin);
	sprites->Add(10069, 274, 1367, 302, 1446, texAladdin);
	sprites->Add(10070, 314, 1377, 346, 1440, texAladdin);
	sprites->Add(10071, 356, 1377, 398, 1439, texAladdin);
	sprites->Add(10072, 406, 1362, 434, 1443, texAladdin);
	//pushing right
	sprites->Add(10073, 7, 1959, 63, 2005, texAladdin);
	sprites->Add(10074, 75, 1961, 140, 2005, texAladdin);
	sprites->Add(10075, 157, 1961, 227, 2006, texAladdin);
	sprites->Add(10076, 237, 1962, 314, 2006, texAladdin);
	sprites->Add(10077, 327, 1964, 399, 2008, texAladdin);
	sprites->Add(10078, 416, 1965, 482, 2009, texAladdin);
	sprites->Add(10079, 495, 1965, 570, 2009, texAladdin);
	sprites->Add(10080, 585, 1966, 666, 2010, texAladdin);
	sprites->Add(10081, 681, 1968, 756, 2012, texAladdin);
	//pushing left
	sprites->Add(-10073, 1058, 1959, 1114, 2005, texAladdin_Left);
	sprites->Add(-10074, 981, 1961, 1046, 2005, texAladdin_Left);
	sprites->Add(-10075, 894, 1961, 964, 2006, texAladdin_Left);
	sprites->Add(-10076, 807, 1962, 884, 2006, texAladdin_Left);
	sprites->Add(-10077, 722, 1964, 794, 2008, texAladdin_Left);
	sprites->Add(-10078, 639, 1965, 705, 2009, texAladdin_Left);
	sprites->Add(-10079, 551, 1965, 626, 2009, texAladdin_Left);
	sprites->Add(-10080, 455, 1966, 536, 2010, texAladdin_Left);
	sprites->Add(-10081, 365, 1968, 440, 2012, texAladdin_Left);
	//dead (ko có left-right)
	sprites->Add(10082, 9, 2167, 51, 2213, texAladdin);
	sprites->Add(10083, 58, 2161, 113, 2213, texAladdin);
	sprites->Add(10084, 122, 2162, 181, 2212, texAladdin);
	sprites->Add(10085, 189, 2163, 269, 2211, texAladdin);
	sprites->Add(10086, 282, 2160, 343, 2211, texAladdin);
	sprites->Add(10087, 351, 2161, 410, 2210, texAladdin);
	sprites->Add(10088, 1, 2234, 81, 2282, texAladdin);
	sprites->Add(10089, 87, 2231, 148, 2282, texAladdin);
	sprites->Add(10090, 160, 2224, 205, 2282, texAladdin);
	sprites->Add(10091, 213, 2224, 258, 2282, texAladdin);
	sprites->Add(10092, 264, 2231, 303, 2281, texAladdin);
	sprites->Add(10093, 312, 2230, 352, 2281, texAladdin);
	sprites->Add(10094, 361, 2230, 396, 2281, texAladdin);
	sprites->Add(10095, 407, 2230, 443, 2281, texAladdin);
	sprites->Add(10096, 454, 2232, 493, 2281, texAladdin);
	sprites->Add(10097, 505, 2227, 549, 2283, texAladdin);
	sprites->Add(10099, 560, 2228, 601, 2281, texAladdin);
	sprites->Add(10100, 614, 2232, 653, 2282, texAladdin);
	sprites->Add(10101, 661, 2232, 701, 2283, texAladdin);
	sprites->Add(10102, 2, 2335, 39, 2386, texAladdin);
	sprites->Add(10103, 49, 2329, 86, 2386, texAladdin);
	sprites->Add(10104, 97, 2331, 140, 2386, texAladdin);
	sprites->Add(10105, 148, 2333, 209, 2386, texAladdin);
	sprites->Add(10106, 223, 2336, 284, 2387, texAladdin);
	sprites->Add(10107, 296, 2310, 372, 2393, texAladdin);
	sprites->Add(10108, 383, 2309, 460, 2394, texAladdin);
	sprites->Add(10109, 476, 2309, 551, 2394, texAladdin);
	sprites->Add(10110, 567, 2311, 635, 2394, texAladdin);
	sprites->Add(10111, 654, 2319, 720, 2394, texAladdin);
	sprites->Add(10112, 734, 2321, 800, 2395, texAladdin);
	sprites->Add(10113, 811, 2323, 877, 2397, texAladdin);
	sprites->Add(10114, 888, 2323, 954, 2397, texAladdin);
	sprites->Add(10115, 970, 2325, 1036, 2399, texAladdin);
	sprites->Add(10116, 1049, 2325, 1115, 2399, texAladdin);
	//climb throw left
	sprites->Add(10117, 13,	1666,	50,	1753, texAladdin);
	sprites->Add(10118, 65,	1666,	106,	1753, texAladdin);
	sprites->Add(10119, 125,	1665,	176,	1753, texAladdin);
	sprites->Add(10120, 192,	1664,	223,	1753, texAladdin);
	sprites->Add(10121, 236,	1664,	293,	1753, texAladdin);
	//climb throw right
	sprites->Add(-10117, 1071,	1666,	1108,	1753, texAladdin_Left);
	sprites->Add(-10118, 1015,	1666,	1056,	1753, texAladdin_Left);
	sprites->Add(-10119, 945,	1665,	996,	1753, texAladdin_Left);
	sprites->Add(-10120, 898,	1664,	929,	1753, texAladdin_Left);
	sprites->Add(-10121, 828,	1664,	885,	1753, texAladdin_Left);
	//climb attack left
	sprites->Add(10122, 15,	1769,	63,	1856, texAladdin);
	sprites->Add(10123, 81,	1769,	133,	1858, texAladdin);
	sprites->Add(10124, 146,	1760,	207,	1862, texAladdin);
	sprites->Add(10125, 222,	1773,	300	,1863, texAladdin);
	sprites->Add(10126, 327,	1773,	382,	1862, texAladdin);
	sprites->Add(10127, 400,	1775,	475,	1864, texAladdin);
	sprites->Add(10128, 499,	1775,	547,	1862, texAladdin);
	//climb attack right
	sprites->Add(-10122, 574,	1775,	622,	1862, texAladdin_Left);
	sprites->Add(-10123, 646,	1775,	718,	1864, texAladdin_Left);
	sprites->Add(-10124, 740,	1773,	794,	1862, texAladdin_Left);
	sprites->Add(-10125, 821,	1773,	899,	1863, texAladdin_Left);
	sprites->Add(-10126, 914,	1760,	975,	1862, texAladdin_Left);
	sprites->Add(-10127, 988,	1769,	1040,	1858, texAladdin_Left);
	sprites->Add(-10128, 1058,	1769,	1106,	1856, texAladdin_Left);
	//climb jump
	sprites->Add(10129, 10,	1870,	44,	1943, texAladdin);
	sprites->Add(10130, 65,	1873,	90,	1950, texAladdin);
	sprites->Add(10131, 100,1874,	136,	1945, texAladdin);
	sprites->Add(10132, 144, 1874,	192,	1938, texAladdin);
	sprites->Add(10133, 204,	1875,	263,	1929, texAladdin);
	sprites->Add(10134, 281,	1876,	340,	1917, texAladdin);
	sprites->Add(10135, 354,	1869,	406,	1923, texAladdin);
	sprites->Add(10136, 422,	1871,	469,	1938, texAladdin);
	sprites->Add(10137, 482,	1866,	527,	1941, texAladdin);
	//running attack right
	sprites->Add(10138, 8,	1293,	43,	1345, texAladdin2);
	sprites->Add(10139, 53,	1285,	104,	1345, texAladdin2);
	sprites->Add(10140, 114,	1292,	164,	1345, texAladdin2);
	sprites->Add(10141, 174,	1285,	222,	1345, texAladdin2);
	sprites->Add(10142, 232,	1285,	305,	1345, texAladdin2);
	sprites->Add(10143, 315,	1295,	375,	1345, texAladdin2);
	//running attack left
	sprites->Add(-10138, 974,	1293,	1009,	1345, texAladdin2_Left);
	sprites->Add(-10139, 913,	1285,	964,	1345, texAladdin2_Left);
	sprites->Add(-10140, 853,	1292,	903,	1345, texAladdin2_Left);
	sprites->Add(-10141, 795,	1285,	843,	1345, texAladdin2_Left);
	sprites->Add(-10142, 712,	1285,	785,	1345, texAladdin2_Left);
	sprites->Add(-10143, 642,	1295,	702,	1345, texAladdin2_Left);
	//running throw right
	sprites->Add(10144, 511,	1297,	548,	1352, texAladdin2);
	sprites->Add(10145, 572,	1295,	621,	1353, texAladdin2);
	sprites->Add(10146, 664,	1297,	713,	1353, texAladdin2);
	sprites->Add(10147, 761,	1291,	814,	1353, texAladdin2);
	sprites->Add(10148, 849,	1291,	893,	1353, texAladdin2);
	sprites->Add(10149, 961,	1301,	996,	1353, texAladdin2);
	//running throw left
	sprites->Add(-10144, 469,	1297,	506,	1352, texAladdin2_Left);
	sprites->Add(-10145, 396,	1295,	445,	1353, texAladdin2_Left);
	sprites->Add(-10146, 304,	1297,	353,	1353, texAladdin2_Left);
	sprites->Add(-10147, 203,	1291,	256,	1353, texAladdin2_Left);
	sprites->Add(-10148, 124,	1291,	168,	1353, texAladdin2_Left);
	sprites->Add(-10149, 21,	1301,	56,	1353, texAladdin2_Left);
	//hurt right
	sprites->Add(10150, 8,	2404,	50,	2450, texAladdin2);
	sprites->Add(10151, 60,	2398,	115,	2450, texAladdin2);
	sprites->Add(10152, 125,	2402,	205,	2450, texAladdin2);
	sprites->Add(10153, 215,	2401,	276,	2450, texAladdin2);
	sprites->Add(10154, 286,	2400,	345,	2450, texAladdin2);
	sprites->Add(10155, 354,	2401,	413,	2450, texAladdin2);
	//hurt left
	sprites->Add(-10150, 967,	2404,	1009,	2450, texAladdin2_Left);
	sprites->Add(-10151, 902,	2398,	957,	2450, texAladdin2_Left);
	sprites->Add(-10152, 812,	2402,	892,	2450, texAladdin2_Left);
	sprites->Add(-10153, 741,	2401,	802,	2450, texAladdin2_Left);
	sprites->Add(-10154, 672,	2400,	731,	2450, texAladdin2_Left);
	sprites->Add(-10155, 604,	2401,	663, 	2450, texAladdin2_Left);
	//health
	sprites->Add(10156, 17,	3007,	137,	3039 , texAladdin2);
	sprites->Add(10157, 147,	3007,	267,	3039, texAladdin2);
	sprites->Add(10158, 277,	3007,	396,	3039, texAladdin2);
	sprites->Add(10159, 406,	3007,	525,	3039, texAladdin2);
	sprites->Add(10160, 17,	3054,	129,	3086, texAladdin2);
	sprites->Add(10161, 139,	3054,	251,	3086, texAladdin2);
	sprites->Add(10162, 261,	3054,	372,	3086, texAladdin2);
	sprites->Add(10163, 382,	3054,	493,	3086, texAladdin2);
	sprites->Add(10164, 17,	3101,	121,	3133, texAladdin2);
	sprites->Add(10165, 131,	3101,	235,	3133, texAladdin2);
	sprites->Add(10166, 245,	3101,	348,	3133, texAladdin2);
	sprites->Add(10167, 358,	3101,	461,	3133, texAladdin2);
	sprites->Add(10168, 17,	3148,	113,	3180, texAladdin2);
	sprites->Add(10169, 123,	3148,	219,	3180, texAladdin2);
	sprites->Add(10170, 229,	3148,	324,	3180, texAladdin2);
	sprites->Add(10171, 334,	3148,	429,	3180, texAladdin2);
	sprites->Add(10172, 17,	3195,	105,	3227, texAladdin2);
	sprites->Add(10173, 116,	3195,	204,	3227, texAladdin2);
	sprites->Add(10174, 214,	3195,	301,	3227, texAladdin2);
	sprites->Add(10175, 311,	3195,	398,	3227, texAladdin2);
	sprites->Add(10176, 17,	3242,	97,	3274, texAladdin2);
	sprites->Add(10177, 107,	3242,	187,	3274, texAladdin2);
	sprites->Add(10178, 197,	3242,	276,	3274, texAladdin2);
	sprites->Add(10179, 286,	3242,	365,	3274, texAladdin2);
	sprites->Add(10180, 17,	3289,	88,	3321, texAladdin2);
	sprites->Add(10181, 98,	3289,	169,	3321, texAladdin2);
	sprites->Add(10182, 179,	3289,	251,	3321, texAladdin2);
	sprites->Add(10183, 261,	3289,	333,	3321, texAladdin2);
	sprites->Add(10184, 17,	3336,	80,	3365, texAladdin2);
	sprites->Add(10185, 90,	3336,	153,	3365, texAladdin2);
	sprites->Add(10186, 163,	3336,	227,	3365, texAladdin2);
	sprites->Add(10187, 237,	3335,	301,	3365, texAladdin2);
	sprites->Add(10188, 17,	3380,	65,	3404, texAladdin2);

#pragma endregion Aladdin
	
#pragma region
	LPDIRECT3DTEXTURE9 texGuards = textures->Get(TEX_GUARD);
	LPDIRECT3DTEXTURE9 texGuardsLeft = textures->Get(TEX_GUARD_LEFT);

	sprites->Add(20001, 99, 11, 135, 76, texGuards);	//sprites for Guards 0 (Staff) walking right
	sprites->Add(20002, 140, 9, 190, 76, texGuards);
	sprites->Add(20003, 196, 9, 239, 76, texGuards);
	sprites->Add(20004, 247, 10, 284, 76, texGuards);
	sprites->Add(20005, 289, 11, 334, 76, texGuards);
	sprites->Add(20006, 343, 11, 389, 76, texGuards);
	sprites->Add(20007, 400, 10, 445, 76, texGuards);
	sprites->Add(20008, 451, 9, 496, 76, texGuards);

	sprites->Add(-20001, 2,	9,	47,	76, texGuardsLeft);	//sprites for Guards 0 (Staff) walking left
	sprites->Add(-20002, 53,	10,	98,	76, texGuardsLeft);
	sprites->Add(-20003, 109,	11,	155,	76, texGuardsLeft);
	sprites->Add(-20004, 164,	11,	209,	76, texGuardsLeft);
	sprites->Add(-20005, 214,	10,	251,	76, texGuardsLeft);
	sprites->Add(-20006, 259,	9,	302,	76, texGuardsLeft);
	sprites->Add(-20007, 308,	9,	358,	76, texGuardsLeft);
	sprites->Add(-20008, 363,	11,	399,	76, texGuardsLeft);

	sprites->Add(20009, 42, 96, 83, 156, texGuards);	//sprites for Guards 0 attack
	sprites->Add(20010, 143, 96, 220, 156, texGuards);
	sprites->Add(20011, 294, 97, 380, 156, texGuards);
	sprites->Add(20012, 472, 98, 564, 156, texGuards);
	sprites->Add(20013, 671, 96, 720, 156, texGuards);
	sprites->Add(20014, 816, 84, 853, 156, texGuards);

	sprites->Add(-20009, 9,	82,	46,	156, texGuardsLeft);	//sprites for Guards 0 attack left
	sprites->Add(-20010, 53,	96,	102,	156, texGuardsLeft);
	sprites->Add(-20011, 109,	98,	201,	156, texGuardsLeft);
	sprites->Add(-20012, 203,	97,	289,	156, texGuardsLeft);
	sprites->Add(-20013, 292,	96,	369,	156, texGuardsLeft);
	sprites->Add(-20014, 382,	96,	423,	156, texGuardsLeft);

	sprites->Add(20015, 20, 166, 65, 233, texGuards); //sprites for Guards 0 hurt
	sprites->Add(20016, 80, 185, 120, 233, texGuards);
	sprites->Add(20017, 133, 184, 180, 233, texGuards);
	sprites->Add(20018, 188, 162, 230, 233, texGuards);
	sprites->Add(20019, 242, 171, 288, 233, texGuards);
	sprites->Add(20020, 296, 165, 337, 233, texGuards);
	sprites->Add(20021, 345, 160, 384, 233, texGuards);
	sprites->Add(20022, 399, 185, 439, 233, texGuards);
	sprites->Add(20023, 446, 175, 490, 233, texGuards);

	sprites->Add(-20015, 8,	175,	52,	233, texGuardsLeft); //sprites for Guards 0 hurt left
	sprites->Add(-20016, 59,	185,	99,	233, texGuardsLeft);
	sprites->Add(-20017, 114,	160,	153,	233, texGuardsLeft);
	sprites->Add(-20018, 161,	165,	202,	233, texGuardsLeft);
	sprites->Add(-20019, 210,	171,	256,	233, texGuardsLeft);
	sprites->Add(-20020, 268,	162,	310,	233, texGuardsLeft);
	sprites->Add(-20021, 318,	184,	365,	233, texGuardsLeft);
	sprites->Add(-20022, 378,	185,	418,	233, texGuardsLeft);
	sprites->Add(-20023, 433,	166,	478,	233, texGuardsLeft);
#pragma endregion Guard Staff

#pragma region
	sprites->Add(21001, 69, 253, 116, 307, texGuards);   //Guard 1 (Blade) walking to the right
	sprites->Add(21002, 120, 251, 164, 307, texGuards);
	sprites->Add(21003, 172, 254, 214, 307, texGuards);
	sprites->Add(21004, 219, 255, 268, 307, texGuards);
	sprites->Add(20005, 274, 253, 325, 307, texGuards);
	sprites->Add(20006, 331, 252, 387, 307, texGuards);
	sprites->Add(20007, 391, 253, 443, 307, texGuards);
	sprites->Add(20008, 449, 255, 496, 307, texGuards);

	sprites->Add(-21001, 2,	255,	49,	307, texGuardsLeft);   //Guard 1 (Blade) walking to the left
	sprites->Add(-21002, 55,	253,	107,	307, texGuardsLeft);
	sprites->Add(-21003, 111,	252,	167,	307, texGuardsLeft);
	sprites->Add(-21004, 173,	253,	224,	307, texGuardsLeft);
	sprites->Add(-20005, 230,	255,	279,	307, texGuardsLeft);
	sprites->Add(-20006, 284,	254,	326,	307, texGuardsLeft);
	sprites->Add(-20007, 334,	251,	378,	307, texGuardsLeft);
	sprites->Add(-20008, 382,	253,	429,	307, texGuardsLeft);

	sprites->Add(20009, 54, 317, 98, 370, texGuards);    //Guard 1 taunt
	sprites->Add(20010, 167, 317, 216, 370, texGuards);
	sprites->Add(20011, 283, 317, 341, 370, texGuards);
	sprites->Add(20012, 392, 317, 446, 370, texGuards);
	sprites->Add(20013, 513, 316, 550, 370, texGuards);
	sprites->Add(20014, 613, 317, 657, 370, texGuards);

	sprites->Add(-20009, 5,	317,	49,	370, texGuardsLeft);    //Guard 1 taunt left
	sprites->Add(-20010, 56,	316,	93,	370, texGuardsLeft);
	sprites->Add(-20011, 98,	317,	152,	370, texGuardsLeft);
	sprites->Add(-20012, 157,	317,	215,	370, texGuardsLeft);
	sprites->Add(-20013, 221,	317,	270,	370, texGuardsLeft);
	sprites->Add(-20014, 278,	317,	322,	370, texGuardsLeft);

	sprites->Add(20015, 67, 384, 162, 430, texGuards); //Guard 1 attack 1
	sprites->Add(20016, 223, 385, 311, 430, texGuards);
	sprites->Add(20016, 376, 387, 451, 430, texGuards);
	sprites->Add(20017, 515, 388, 585, 430, texGuards);
	sprites->Add(20018, 644, 386, 711, 430, texGuards);
	sprites->Add(20019, 761, 378, 816, 430, texGuards);

	sprites->Add(-20015, 6,	378,	61,	430, texGuardsLeft); //Guard 1 attack 1 left
	sprites->Add(-20016, 65,	386,	132,	430, texGuardsLeft);
	sprites->Add(-20016, 140,	388,	210,	430, texGuardsLeft);
	sprites->Add(-20017, 216,	387,	291,	430, texGuardsLeft);
	sprites->Add(-20018, 297,	385,	385,	430, texGuardsLeft);
	sprites->Add(-20019, 395,	384,	490,	430, texGuardsLeft);

	sprites->Add(20020, 44, 440, 132, 513, texGuards); //Guard 1 attack 2
	sprites->Add(20021, 206, 451, 320, 507, texGuards);
	sprites->Add(20022, 330, 441, 382, 507, texGuards);
	sprites->Add(20023, 434, 434, 477, 507, texGuards);
	sprites->Add(20024, 550, 447, 593, 507, texGuards);

	sprites->Add(-20020, 6,	447,	49,	507, texGuardsLeft); //Guard 1 attack 2 left
	sprites->Add(-20021, 61,	434,	104,	507, texGuardsLeft);
	sprites->Add(-20022, 116,	441,	168,	507, texGuardsLeft);
	sprites->Add(-20023, 178,	451,	292,	507, texGuardsLeft);
	sprites->Add(-20024, 300,	434,	391,	507, texGuardsLeft);

	sprites->Add(20025, 50, 530, 116, 586, texGuards); //Guard 1 hurt
	sprites->Add(20026, 134, 522, 208, 586, texGuards);
	sprites->Add(20027, 217, 520, 288, 586, texGuards);
	sprites->Add(20028, 295, 529, 360, 586, texGuards);
	sprites->Add(20029, 364, 515, 427, 586, texGuards);
	sprites->Add(20030, 438, 538, 492, 586, texGuards);

	sprites->Add(-20025, 6,	538,	60,	586, texGuardsLeft); //Guard 1 hurt left
	sprites->Add(-20026, 71,	515,	134,	586, texGuardsLeft);
	sprites->Add(-20027, 138,	529,	203,	586, texGuardsLeft);
	sprites->Add(-20028, 210,	520,	281,	586, texGuardsLeft);
	sprites->Add(-20029, 290,	522,	364,	586, texGuardsLeft);
	sprites->Add(-20030, 382,	530,	448,	586, texGuardsLeft);

#pragma endregion Guard Blade

#pragma region
	LPDIRECT3DTEXTURE9 texExplodeSkeleton = textures->Get(TEX_EXPLODE_SKELETON);
	
	sprites->Add(22000, 8,	73,	94,	99, texExplodeSkeleton);			 //Skeleton Create
	sprites->Add(22001, 101,	72,	181,	97, texExplodeSkeleton);
	sprites->Add(22002, 188,	52,	263,	97, texExplodeSkeleton);
	sprites->Add(22003, 283,	37,	345,	97, texExplodeSkeleton);
	sprites->Add(22004, 365,	29,	415,	96, texExplodeSkeleton);
	sprites->Add(22005, 427,	25,	475,	96, texExplodeSkeleton);
	sprites->Add(22006, 486,	22,	534,	97, texExplodeSkeleton);

	sprites->Add(22007, 544,	16,	595, 97, texExplodeSkeleton);		//Skeleton Exploding
	sprites->Add(22008, 601,	16,	652,	97, texExplodeSkeleton);
	sprites->Add(22009, 662,	17,	714,	97, texExplodeSkeleton);
	sprites->Add(22010, 726,	16,	794,	97, texExplodeSkeleton);
	sprites->Add(22011, 799,	8,	864,	97, texExplodeSkeleton);
	sprites->Add(22012, 13,	122,	63,	204, texExplodeSkeleton);
	sprites->Add(22013, 75,	123,	124,	204, texExplodeSkeleton);
	sprites->Add(22014, 132,	121,	193,	205, texExplodeSkeleton);
	sprites->Add(22015, 203,	130,	267,	205, texExplodeSkeleton);
	sprites->Add(22016, 279,	121,	353,	206, texExplodeSkeleton);
	sprites->Add(22017, 376,	115,	457,	206, texExplodeSkeleton);
	sprites->Add(22018, 479,	126,	574,	203, texExplodeSkeleton);
	sprites->Add(22019, 593,	125,	653,	204, texExplodeSkeleton);

#pragma endregion Explode Skeleton

#pragma region
    LPDIRECT3DTEXTURE9 texEnemyExplode = textures->Get(TEX_ENEMY_EXPLODE);
	sprites->Add(20031, 20,	30,	32,	40, texEnemyExplode); //Enemy explode
	sprites->Add(20032, 54,	15,	95,	42, texEnemyExplode);
	sprites->Add(20033, 102,	15,	149,	43, texEnemyExplode);
	sprites->Add(20034, 148,	14,	195,	42, texEnemyExplode);
	sprites->Add(20035, 197,	12,	246,	42, texEnemyExplode);
	sprites->Add(20036, 246,	12,	294,	42, texEnemyExplode);
	sprites->Add(20037, 305,	22,	329,	43, texEnemyExplode);
	sprites->Add(20038, 355,	23,	378,	43, texEnemyExplode);
	sprites->Add(20039, 405,	24,	428,	43, texEnemyExplode);
	sprites->Add(20040, 454,	24,	475,	43, texEnemyExplode);
#pragma endregion Enemy Dead

#pragma region 
	LPDIRECT3DTEXTURE9 texDungeonObjects = textures->Get(TEX_DUNGEON_ENVIRONMENT);
	
	sprites->Add(-30001, 177, 5, 217, 346, texDungeonObjects); //pillar 0

	sprites->Add(-30002, 497, 2, 529, 162, texDungeonObjects); //pillar 1

	sprites->Add(-30003, 817, 2, 849, 746, texDungeonObjects);   //pillar 2

	sprites->Add(-30004, 1169, 2, 1201, 194, texDungeonObjects); //pillar 3

	sprites->Add(-30005, 1, 351, 513, 607, texDungeonObjects);   //front_chains

	sprites->Add(-30007, 1, 628, 32, 643, texDungeonObjects);    //step-in
	sprites->Add(-30008, 37, 628, 68, 643, texDungeonObjects);
	sprites->Add(-30009, 73, 628, 107, 645, texDungeonObjects);

	sprites->Add(-30010, 112, 628, 150, 649, texDungeonObjects);  //step-out
	sprites->Add(-30011, 155, 628, 195, 652, texDungeonObjects);

	sprites->Add(-30012, 1, 657, 24, 677, texDungeonObjects);  //spike-in
	sprites->Add(-30013, 29, 657, 52, 680, texDungeonObjects);
	sprites->Add(-30014, 57, 657, 83, 685, texDungeonObjects);
	sprites->Add(-30015, 88, 657, 121, 688, texDungeonObjects);

	sprites->Add(-30016, 126, 657, 168, 691, texDungeonObjects); //spike-out
	sprites->Add(-30017, 173, 657, 222, 692, texDungeonObjects);

	sprites->Add(-30018, 227, 628, 241, 673, texDungeonObjects); //ball-in
	sprites->Add(-30019, 246, 628, 261, 675, texDungeonObjects);
	sprites->Add(-30020, 266, 628, 281, 678, texDungeonObjects);
	sprites->Add(-30021, 286, 628, 301, 680, texDungeonObjects);
	sprites->Add(-30022, 306, 628, 322, 684, texDungeonObjects);
	sprites->Add(-30023, 306, 628, 343, 688, texDungeonObjects);
	sprites->Add(-30024, 348, 628, 366, 693, texDungeonObjects);
	sprites->Add(-30025, 371, 628, 392, 695, texDungeonObjects);
	sprites->Add(-30026, 397, 628, 423, 693, texDungeonObjects);
	sprites->Add(-30027, 428, 628, 456, 691, texDungeonObjects);
	sprites->Add(-30028, 461, 628, 491, 687, texDungeonObjects);
	sprites->Add(-30029, 496, 628, 527, 685, texDungeonObjects);
	
	sprites->Add(-30030, 532, 628, 564, 684, texDungeonObjects);  //ball-out
	sprites->Add(-30031, 569, 628, 602, 681, texDungeonObjects);
	sprites->Add(-30032, 607, 628, 640, 680, texDungeonObjects);

#pragma endregion Dungeon_Objects

#pragma region
    LPDIRECT3DTEXTURE9 texApple = textures->Get(TEX_APPLE);

    sprites->Add(40001, 8, 18, 19, 30, texApple); // idle apple
    //sprites->Add(20002, 35, 19, 47, 30, texApple);
    //sprites->Add(20003, 62, 19, 73, 31, texApple);
    //sprites->Add(20004, 87, 19, 99, 30, texApple);
    //sprites->Add(20005, 113, 20, 120, 30, texApple);
    //sprites->Add(20006, 133, 15, 153, 33, texApple);
    //sprites->Add(20007, 163, 13, 192, 35, texApple);
    //sprites->Add(20008, 240, 11, 235, 36, texApple);
    //sprites->Add(20009, 251, 10, 281, 37, texApple);
#pragma endregion Throw Apple

#pragma region
    LPDIRECT3DTEXTURE9 texItemDestroy = textures->Get(TEX_ITEM_DESTROY);

    sprites->Add(-40001, 11, 19, 17, 25, texItemDestroy);
    sprites->Add(-40002, 53, 13, 63, 29, texItemDestroy);
    sprites->Add(-40003, 97, 11, 109, 29, texItemDestroy);
    sprites->Add(-40004, 135, 7, 157, 31, texItemDestroy);
    sprites->Add(-40005, 175, 5, 209, 37, texItemDestroy);
    sprites->Add(-40006, 219, 1, 233, 35, texItemDestroy);
    sprites->Add(-40007, 239, 5, 277, 39, texItemDestroy);
    sprites->Add(-40008, 285, 7, 317, 35, texItemDestroy);
    sprites->Add(-40009, 325, 11, 359, 37, texItemDestroy);
    sprites->Add(-40010, 369, 15, 403, 37, texItemDestroy);
    sprites->Add(-40011, 417, 19, 451, 39, texItemDestroy);
    sprites->Add(-40012, 461, 25, 473, 39, texItemDestroy);
#pragma endregion Item Destroy

#pragma region
	LPDIRECT3DTEXTURE9 texItem = textures->Get(TEX_ITEM);

	//genie
	sprites->Add(50001, 335,	45,	373,	95, texItem);		
	sprites->Add(50002, 389,	45,	432,	97, texItem);
	sprites->Add(50003, 443,	49,	487,	93, texItem);
	sprites->Add(50004, 497,	48,	542,	92, texItem);
		
	//ruby
	sprites->Add(50005, 340,	111,	357,	127, texItem);	
	sprites->Add(50006, 363,	111,	380,	127, texItem);
	sprites->Add(50007, 386,	111,	403,	127, texItem);
	sprites->Add(50008, 409,	111,	426,	127, texItem);
	sprites->Add(50009, 432,	110,	449,	127, texItem);
	sprites->Add(50010, 454,	107,	486,	128, texItem);
	sprites->Add(50011, 492,	110,	515,	128, texItem);
	sprites->Add(50012, 522,	112,	539,	128, texItem);
	sprites->Add(50013, 545,	112,	562,	128, texItem);

	//save idle
	sprites->Add(50014, 19,	424, 39,	457, texItem);			

	//save eaten
	sprites->Add(50015, 49,	428,	73,	457, texItem);			
	sprites->Add(50016, 78,	437,	112,	457, texItem);
	sprites->Add(50017, 119,	425,	139,	459, texItem);
	sprites->Add(50018, 145,	425,	168,	459, texItem);
	sprites->Add(50019, 174,	426,	200,	459, texItem);
	sprites->Add(50020, 207,	426,	231,	460, texItem);
	sprites->Add(50021, 239,	427,	259,	461, texItem);
	sprites->Add(50022, 270,	428,	294,	461, texItem);
	sprites->Add(50023, 302,	429,	325,	462, texItem);

	//life
	sprites->Add(50024, 343,	171,	362,	195, texItem);			
	sprites->Add(50025, 366,	173,	383,	196, texItem);
	sprites->Add(50026, 387,	175,	403,	196, texItem);
	sprites->Add(50027, 406,	175,	423,	196, texItem);
	sprites->Add(50028, 426,	173,	445,	196, texItem);
	sprites->Add(50029, 448,	174,	466,	196, texItem);
	sprites->Add(50030, 466,	174,	483,	196, texItem);
	sprites->Add(50031, 486,	176,	503,	197, texItem);

	//face
	sprites->Add(50032, 340,	140,	362,	164, texItem);			

#pragma endregion Items

#pragma region
	LPDIRECT3DTEXTURE9 texMenu = textures->Get(TEX_MAIN_MENU);
	LPDIRECT3DTEXTURE9 texLevelComplete = textures->Get(TEX_LEVEL_COMPLETE);
	LPDIRECT3DTEXTURE9 texAbu = textures->Get(TEX_ABU);

	sprites->Add(60001, 0, 0, 421, 256, texMenu);	//main menu

	sprites->Add(60002, 0, 0, 636, 445, texLevelComplete); //level complete
		
	sprites->Add(60003, 3,	2565,	47,	2627, texAladdin); //aladdin level complete
	sprites->Add(60004, 60,	2566,	109,	2625, texAladdin);
	sprites->Add(60005, 123,	2566,	158,	2623, texAladdin);
	sprites->Add(60006, 166,	2565,	206,	2626, texAladdin);
	sprites->Add(60007, 215,	2567,	251,	2627, texAladdin);
	sprites->Add(60008, 263,	2564,	301,	2627, texAladdin);
	sprites->Add(60009, 310,	2565,	358,	2624, texAladdin);
	sprites->Add(60010, 372,	2564,	409,	2625, texAladdin);

	sprites->Add(60012, 33,	15,	59,	48, texAbu);		//abu level complete
	sprites->Add(60013, 81,	15,	123,	48, texAbu);
	sprites->Add(60014, 137,	15,	189,	47, texAbu);
	sprites->Add(60015, 208,	11,	248,	48, texAbu);
	sprites->Add(60016, 276,	12,	311,	48, texAbu);
	sprites->Add(60017, 331,	12,	376,	48, texAbu);
	sprites->Add(60018, 395,	14,	445,	48, texAbu);
	sprites->Add(60019, 457,	17,	503,	48, texAbu);


#pragma endregion Scenes
    //Ground
    LPDIRECT3DTEXTURE9 texGround = textures->Get(TEX_GROUND);  
    sprites->Add(30001, 10, 10, 100, 100, texGround);
}

void ResourceLoader::LoadObjectFromFile(string FileName, vector<LPGAMEOBJECT>& objects)
{
	int object_index = 1;

	std::ifstream infile(FileName);
	string name;
	float  x, y, w, h;
	while (infile >> name >> x >> y >> w >> h)
	{
		//Chuyen toa do y theo goc toa do cua file txt thanh toa do decart
		ChangeYtoDecart(y);

        if (name == GROUND0_ID)
        {
            Ground* ground0 = new Ground();
            ground0->type = 0;
            ground0->AddAnimation(301);
            ground0->SetPosition(x, y);
            ground0->SetName(name);
            ground0->width = w;
            ground0->height = h;
			ground0->id = object_index;
            objects.push_back(ground0);
        }
        else if (name == GROUND1_ID || name == "Ground3")
        {
            Ground* ground1 = new Ground();
            ground1->type = 1;
            ground1->AddAnimation(301);
            ground1->SetPosition(x, y);
            ground1->SetName(name);
            ground1->width = w;
            ground1->height = h;
			ground1->id = object_index;
            objects.push_back(ground1);
        }
        else if (name == APPLE_ID)
        {
            Apple* apple = new Apple();
            apple->AddAnimation(401); //apple idle
            apple->AddAnimation(ITEM_DESTROY);
            apple->SetPosition(x, y);
            apple->SetName(name);
            apple->width = w;
            apple->height = h;
			apple->id = object_index;
            objects.push_back(apple);
        }
        else if (name == PILLAR0_ID || name == PILLAR1_ID || name == PILLAR2_ID || name == PILLAR3_ID || name == FRONT_CHAINS_ID)
        {
            Ground* ground0 = new Ground();
            if(name == PILLAR0_ID)
                ground0->AddAnimation(-301);
            else if (name == PILLAR1_ID)
                ground0->AddAnimation(-302);
            else if (name == PILLAR2_ID)
                ground0->AddAnimation(-303);
            else if (name == PILLAR3_ID)
                ground0->AddAnimation(-304);
            else
                ground0->AddAnimation(-305);
            ground0->SetPosition(x, y);
            ground0->SetName(name);
            ground0->width = w;
            ground0->height = h;
			ground0->id = object_index;
            objects.push_back(ground0);
        }

		object_index++;
	}
}

void ResourceLoader::LoadMapFromFile(string FileName, LPDIRECT3DTEXTURE9 texMap, vector<LPGAMEOBJECT>& map_vector)
{
	std::ifstream infile(FileName);
	string name;
	float  x, y, w, h;
	while (infile >> name >> x >> y >> w >> h)
	{
		//Add sprite 1 vào cell map 1
		CSprites* sprites = CSprites::GetInstance();
		sprites->Add(40001, x, y, x + w, y + h, texMap);

		LPANIMATION ani;
		ani = new CAnimation(100);
		ani->Add(40001);
		CAnimations* animations = CAnimations::GetInstance();
		animations->Add(801, ani);

		ChangeYtoDecart(y);
		//khởi tạo cell map
		CMap* map1 = new CMap();

		map1->AddAnimation(801);
		map1->width = w;
		map1->height = h;
		map1->SetPosition(x, y);
        map1->SetName(name);
		map_vector.push_back(map1);
	}
}

vector<int> ResourceLoader::read_map(string file_path)
{
	ifstream map_file(file_path);
	vector<int> result;
	if (map_file.is_open())
	{
		while (true)
		{
			int x;
			map_file >> x;
			if (map_file.eof())
				break;
			result.push_back(x);
		}
		map_file.close();
	}
	return result;
};

// Load map từ file ma trận
void ResourceLoader::load_tile_map(LPDIRECT3DTEXTURE9 tile_set, string file_path, vector<LPGAMEOBJECT>& map_vector)
{
	CSprites* sprites = CSprites::GetInstance();
	vector<int> arr = ResourceLoader::read_map(file_path);

	int tile_set_count = arr[0];
	int tile_map_row = arr[1];
	int tile_map_column = arr[2];
	int tile_height = arr[3];
	int tile_width = arr[4];
	int tile_set_row = arr[5];
	int tile_set_column = arr[6];

	//tile_count = tile_set_count;

	arr.erase(arr.begin(), arr.begin() + 7);

	//duyệt tileset để lấy sprite
	for (int i = 0; i < tile_set_count; i++)
	{
		int l = (i % tile_set_column) * tile_width;
		int t = (i / tile_set_column) * tile_height;
		int r = l + tile_width;
		int b = t + tile_height;
		sprites->Add(TILE_INDEX + i, l, t, r, b, tile_set);
	}

	//duyệt ma trận
	for (int i = 0; i < arr.size(); i++)
	{
		float l = (float)((i % tile_map_column) * tile_width);
		float t = (float)((i / tile_map_column) * tile_height);

		LPANIMATION ani;
		ani = new CAnimation(100);
		ani->Add(TILE_INDEX + arr[i]);
		CAnimations* animations = CAnimations::GetInstance();
		animations->Add(2222, ani);

		ChangeYtoDecart(t);
		l += 64;	//fix position, map bị lệch 1 tile
		//khởi tạo cell map
		CMap* map1 = new CMap();

		map1->AddAnimation(2222);
		map1->width = tile_height;
		map1->height = tile_height;
		map1->SetPosition(l, t);
		map_vector.push_back(map1);
		// Tiles.push_back(new Tile((float)l, (float)t, sprites->Get(TILE_INDEX + arr[i])));
	}

	//temp fix first column not show (aladdin dungeon map only)
	for (int i = 0; i < tile_map_row; i++)
	{
		float l = 0;
		float t = (float)(i * tile_height);

		LPANIMATION ani;
		ani = new CAnimation(100);
		ani->Add(TILE_INDEX + arr[i * tile_map_column] - 1);
		CAnimations* animations = CAnimations::GetInstance();
		animations->Add(22222, ani);

		ChangeYtoDecart(t);
		//khởi tạo cell map
		CMap* map1 = new CMap();

		map1->AddAnimation(22222);
		map1->width = tile_height;
		map1->height = tile_height;
		map1->SetPosition(l, t);
		map_vector.push_back(map1);
	}
};

void ResourceLoader::ChangeYtoDecart(float& y)
{
	y = MAP_HEIGHT + 30 - y; //38 la do lech pixel o duoi man hinh
}
