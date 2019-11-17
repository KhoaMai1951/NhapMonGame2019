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
    ani = new CAnimation(75);
    for (int i = 14; i <= 23; i++)
    {
        ani->Add(aladdin_sprite_id + i);
    }
    animations->Add(103, ani);

    //jump left
    ani = new CAnimation(75);
    for (int i = 14; i <= 23; i++)
    {
        ani->Add(-(aladdin_sprite_id + i));
    }
    animations->Add(-103, ani);

#pragma endregion Aladdin

    //Animation ground
    ani = new CAnimation(75);
    ani->Add(30001);
    animations->Add(301, ani);

    //ani = new CAnimation(100);	// idle big right
    //ani->Add(10001);
    //animations->Add(400, ani);

    //ani = new CAnimation(100);	// idle big left
    //ani->Add(10011);
    //animations->Add(401, ani);

    //ani = new CAnimation(100);	// idle small right
    //ani->Add(10021);
    //animations->Add(402, ani);

    //ani = new CAnimation(100);	// idle small left
    //ani->Add(10031);
    //animations->Add(403, ani);

    //ani = new CAnimation(100);	// walk right big
    //ani->Add(10001);
    //ani->Add(10002);
    //ani->Add(10003);
    //animations->Add(500, ani);

    //ani = new CAnimation(100);	// // walk left big
    //ani->Add(10011);
    //ani->Add(10012);
    //ani->Add(10013);
    //animations->Add(501, ani);

    //ani = new CAnimation(100);	// walk right small
    //ani->Add(10021);
    //ani->Add(10022);
    //ani->Add(10023);
    //animations->Add(502, ani);

    //ani = new CAnimation(100);	// walk left small
    //ani->Add(10031);
    //ani->Add(10032);
    //ani->Add(10033);
    //animations->Add(503, ani);


    //ani = new CAnimation(100);		// Mario die
    //ani->Add(10099);
    //animations->Add(599, ani);


    //ani = new CAnimation(100);		// brick
    //ani->Add(20001);
    //animations->Add(601, ani);

    //ani = new CAnimation(300);		// Goomba walk
    //ani->Add(30001);
    //ani->Add(30002);
    //animations->Add(701, ani);

    //ani = new CAnimation(1000);		// Goomba dead
    //ani->Add(30003);
    //animations->Add(702, ani);
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
	
    ////temp
    //textures->Add(ID_TEX_MARIO, L"textures\\mario.png", D3DCOLOR_XRGB(255, 255, 255));
    //textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
    //textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));



    CSprites* sprites = CSprites::GetInstance();

#pragma region
    LPDIRECT3DTEXTURE9 texAladdin = textures->Get(TEX_ALADDIN);
    LPDIRECT3DTEXTURE9 texAladdin_Left = textures->Get(TEX_ALADDIN_LEFT);

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
    sprites->Add(-10008, 694, 1221, 690, 1273, texAladdin_Left);
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

    sprites->Add(-10014, 523, 812, 557, 905, texAladdin); //jump left
    sprites->Add(-10015, 583, 810, 617, 903, texAladdin);
    sprites->Add(-10016, 639, 808, 673, 901, texAladdin);
    sprites->Add(-10017, 696, 818, 731, 897, texAladdin);
    sprites->Add(-10018, 747, 829, 785, 895, texAladdin);
    sprites->Add(-10019, 801, 820, 852, 894, texAladdin);
    sprites->Add(-10020, 864, 824, 918, 893, texAladdin);
    sprites->Add(-10021, 930, 829, 984, 890, texAladdin);
    sprites->Add(-10022, 994, 828, 1046, 890, texAladdin);
    sprites->Add(-10023, 1054, 846, 1113, 889, texAladdin);

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

	sprites->Add(-30005, 1, 351, 513, 607, texDungeonObjects);   //chains_front

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

    sprites->Add(20001, 8, 18, 19, 30, texApple);		// idle apple
    sprites->Add(20002, 35, 19, 47, 30, texApple);
    sprites->Add(20003, 62, 19, 73, 31, texApple);
    sprites->Add(20004, 87, 19, 99, 30, texApple);
    sprites->Add(20005, 113, 20, 120, 30, texApple);
    sprites->Add(20006, 133, 15, 153, 33, texApple);
    sprites->Add(20007, 163, 13, 192, 35, texApple);
    sprites->Add(20008, 240, 11, 235, 36, texApple);
    sprites->Add(20009, 251, 10, 281, 37, texApple);
#pragma region Apple

    //Ground
    LPDIRECT3DTEXTURE9 texGround = textures->Get(TEX_GROUND);  
    sprites->Add(30001, 10, 10, 100, 100, texGround);

    //LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);
    //// Mario big
    //sprites->Add(10001, 246, 154, 260, 181, texMario);		// idle right

    //sprites->Add(10002, 275, 154, 290, 181, texMario);		// walk
    //sprites->Add(10003, 304, 154, 321, 181, texMario);

    //sprites->Add(10011, 186, 154, 200, 181, texMario);		// idle left
    //sprites->Add(10012, 155, 154, 170, 181, texMario);		// walk
    //sprites->Add(10013, 125, 154, 140, 181, texMario);

    //sprites->Add(10099, 215, 120, 231, 135, texMario);		// die 

    //// Mario small
    //sprites->Add(10021, 247, 0, 259, 15, texMario);			// idle small right
    //sprites->Add(10022, 275, 0, 291, 15, texMario);			// walk 
    //sprites->Add(10023, 306, 0, 320, 15, texMario);			// 

    //sprites->Add(10031, 187, 0, 198, 15, texMario);			// idle small left

    //sprites->Add(10032, 155, 0, 170, 15, texMario);			// walk
    //sprites->Add(10033, 125, 0, 139, 15, texMario);			// 

    //// Platform
    //LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
    //sprites->Add(20001, 408, 225, 424, 241, texMisc);

    //// Enemy
    //LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
    //sprites->Add(30001, 5, 14, 21, 29, texEnemy);
    //sprites->Add(30002, 25, 14, 41, 29, texEnemy);

    //sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite
}

void ResourceLoader::LoadObjectFromFile(string FileName, vector<LPGAMEOBJECT>& objects)
{
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
            ground0->AddAnimation(301);
            ground0->SetPosition(x, y);
            ground0->SetName(name);
            ground0->width = w;
            ground0->height = h;
            objects.push_back(ground0);
        }

		/*if (name == BRICK_ID)
		{
			CBrick* brick = new CBrick();
			brick->AddAnimation(601);
			brick->SetPosition(x, y);
            brick->SetName(name);
            brick->width = w;
            brick->height = h;
			objects.push_back(brick);
		}
		if (name == GOOMBA_ID)
		{
			CGoomba* goomba = new CGoomba();
			goomba->AddAnimation(701);
			goomba->AddAnimation(702);
			goomba->SetPosition(x, y);
            goomba->SetName(name);
            goomba->width = w;
            goomba->height = h;
            goomba->SetState(GOOMBA_STATE_WALKING);
			objects.push_back(goomba);
		}*/
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
	y = MAP_HEIGHT + 38 - y; //38 la do lech pixel o duoi man hinh
}
