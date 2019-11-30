#include "ResourceLoader.h"
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
    ani->Add(100012,750);
    ani->Add(100013);
    ani->Add(100014);
    ani->Add(100015);
    ani->Add(100016,750);
    ani->Add(100017);
    animations->Add(1011, ani);

    //idle2
    ani = new CAnimation(100);
    for (int i = 17; i <= 31; i++)
    {
        ani->Add(100000 + i);
    }
    ani->Add(100032,750);       //Sprite 15 of animation
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

#pragma endregion Aladdin

#pragma region
    //Animation apple
    ani = new CAnimation(100);
    ani->Add(40001);
    animations->Add(401, ani);
    ani = new CAnimation(75); //item destroy of apple
    for (int i = 1; i <= 12; i++)
        ani->Add(-40000 - i);
    animations->Add(ITEM_DESTROY, ani);
#pragma endregion Items

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

    CSprites* sprites = CSprites::GetInstance();

#pragma region
    LPDIRECT3DTEXTURE9 texAladdin = textures->Get(TEX_ALADDIN);
    LPDIRECT3DTEXTURE9 texAladdin_Left = textures->Get(TEX_ALADDIN_LEFT);

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


#pragma endregion Aladdin
	
#pragma region
	LPDIRECT3DTEXTURE9 texGuards = textures->Get(TEX_GUARD);

	sprites->Add(-20001, 99, 11, 135, 76, texGuards);	//sprites for Guards 0 walking right
	sprites->Add(-20002, 140, 9, 190, 76, texGuards);
	sprites->Add(-20003, 196, 9, 239, 76, texGuards);
	sprites->Add(-20004, 247, 10, 284, 76, texGuards);
	sprites->Add(-20005, 289, 11, 334, 76, texGuards);
	sprites->Add(-20006, 343, 11, 389, 76, texGuards);
	sprites->Add(-20007, 400, 10, 445, 76, texGuards);
	sprites->Add(-20008, 451, 9, 496, 76, texGuards);

	sprites->Add(-20009, 42, 96, 83, 156, texGuards);	//sprites for Guards 0 attack
	sprites->Add(-20010, 143, 96, 220, 156, texGuards);
	sprites->Add(-20011, 294, 97, 380, 156, texGuards);
	sprites->Add(-20012, 472, 98, 564, 156, texGuards);
	sprites->Add(-20013, 671, 96, 720, 156, texGuards);
	sprites->Add(-20014, 816, 84, 853, 156, texGuards);

	sprites->Add(-20015, 20, 166, 65, 233, texGuards); //sprites for Guards 0 hurt
	sprites->Add(-20016, 80, 185, 120, 233, texGuards);
	sprites->Add(-20017, 133, 184, 180, 233, texGuards);
	sprites->Add(-20018, 188, 162, 230, 233, texGuards);
	sprites->Add(-20019, 242, 171, 288, 233, texGuards);
	sprites->Add(-20020, 296, 165, 337, 233, texGuards);
	sprites->Add(-20021, 345, 160, 384, 233, texGuards);
	sprites->Add(-20022, 399, 185, 439, 233, texGuards);
	sprites->Add(-20023, 446, 175, 490, 233, texGuards);
#pragma endregion Guard 0

#pragma region
	sprites->Add(-20001, 69, 253, 116, 307, texGuards);   //Guard 1 walking to the right
	sprites->Add(-20002, 120, 251, 164, 307, texGuards);
	sprites->Add(-20003, 172, 254, 214, 307, texGuards);
	sprites->Add(-20004, 219, 255, 268, 307, texGuards);
	sprites->Add(-20005, 274, 253, 325, 307, texGuards);
	sprites->Add(-20006, 331, 252, 387, 307, texGuards);
	sprites->Add(-20007, 391, 253, 443, 307, texGuards);
	sprites->Add(-20008, 449, 255, 496, 307, texGuards);

	sprites->Add(-20009, 54, 317, 98, 370, texGuards);    //Guard 1 taunt
	sprites->Add(-20010, 167, 317, 216, 370, texGuards);
	sprites->Add(-20011, 283, 317, 341, 370, texGuards);
	sprites->Add(-20012, 392, 317, 446, 370, texGuards);
	sprites->Add(-20013, 513, 316, 550, 370, texGuards);
	sprites->Add(-20014, 613, 317, 657, 370, texGuards);

	sprites->Add(-20015, 67, 384, 162, 430, texGuards); //Guard 1 attack 1
	sprites->Add(-20016, 223, 385, 311, 430, texGuards);
	sprites->Add(-20016, 376, 387, 451, 430, texGuards);
	sprites->Add(-20017, 515, 388, 585, 430, texGuards);
	sprites->Add(-20018, 644, 386, 711, 430, texGuards);
	sprites->Add(-20019, 761, 378, 816, 430, texGuards);

	sprites->Add(-20020, 44, 440, 132, 513, texGuards); //Guard 1 attack 2
	sprites->Add(-20021, 206, 451, 320, 507, texGuards);
	sprites->Add(-20022, 330, 441, 382, 507, texGuards);
	sprites->Add(-20023, 434, 434, 477, 507, texGuards);
	sprites->Add(-20024, 550, 447, 593, 507, texGuards);

	sprites->Add(-20025, 50, 530, 116, 586, texGuards); //Guard 1 hurt
	sprites->Add(-20026, 134, 522, 208, 586, texGuards);
	sprites->Add(-20027, 217, 520, 288, 586, texGuards);
	sprites->Add(-20028, 295, 529, 360, 586, texGuards);
	sprites->Add(-20029, 364, 515, 427, 586, texGuards);
	sprites->Add(-20030, 438, 538, 492, 586, texGuards);

#pragma endregion Guard 1

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

void ResourceLoader::ChangeYtoDecart(float& y)
{
	y = MAP_HEIGHT + 30 - y; //38 la do lech pixel o duoi man hinh
}
