#include "Boss_Scene.h"


Boss_Scene::Boss_Scene()
{

};

void Boss_Scene::Initialize()
{
	ViewPort::getInstance()->setPositionWorld(D3DXVECTOR2(0, SCREEN_HEIGHT));

	Sound::getInstance()->play("SCENE_BOSS", true, 0);

	//----------Load Map từ file text và Tile Set
	CSprites* sprites = CSprites::GetInstance();

	CTextures* textures = CTextures::GetInstance();

	LPANIMATION ani;
	CAnimations* animations = CAnimations::GetInstance();

	textures->Add(TEX_MAP_BOSS, L"textures\\palace.png", D3DCOLOR_XRGB(255, 255, 255));
    textures->Add(TEX_MAP_BOSS_BACK, L"textures\\SceneBoss_Back.png", D3DCOLOR_XRGB(255, 255, 255));

	sprites->Add(99999, 0, 0, 830, 450, textures->Get(TEX_MAP_BOSS));
	ani = new CAnimation(100);
	ani->Add(99999);
	animations->Add(ANI_BOSS_MAP, ani);
    sprites->Add(99998, 0, 0, 896, 360, textures->Get(TEX_MAP_BOSS_BACK));
    ani = new CAnimation(100);
    ani->Add(99998);
    animations->Add(ANI_BOSS_MAP_BACK, ani);

	//ResourceLoader::GetInstance()->load_tile_map(texBossTileSet, "Map_Matrix_Boss_Scene.txt", map_vector);

    map = new CMap();
    map->AddAnimation(ANI_BOSS_MAP);
    map->SetPosition(0, BOSS_MAP_HEIGHT);
    map->width = BOSS_MAP_WIDTH;
    map->height = BOSS_MAP_HEIGHT;

    back = new CMap();
    back->AddAnimation(ANI_BOSS_MAP_BACK);
    back->SetPosition(0, BOSS_MAP_HEIGHT);
    back->width = 896;
    back->height = 360;

	//----------------------------------------------
#pragma region 
	aladdin = new Aladdin();
	aladdin->SetScene(this);
	aladdin->AddAnimation(101); //idle right 
	aladdin->AddAnimation(-101); //idle left 
	aladdin->AddAnimation(102); //running right
	aladdin->AddAnimation(-102); //running left
	aladdin->AddAnimation(103); //jump right
	aladdin->AddAnimation(-103); //jump left
	aladdin->AddAnimation(104); //run jump right
	aladdin->AddAnimation(-104); //run jump left
	aladdin->AddAnimation(105); //look up
	aladdin->AddAnimation(-105); //look up
	aladdin->AddAnimation(106); //crouch   
	aladdin->AddAnimation(-106); //crouch
	aladdin->AddAnimation(1011); //idle1
	aladdin->AddAnimation(1012); //idle2
	aladdin->AddAnimation(1013); //idle3

	aladdin->AddAnimation(107);  //attack right
	aladdin->AddAnimation(-107); //attack left
	aladdin->AddAnimation(108); //throw apple right standing
	aladdin->AddAnimation(-108); //throw apple left standing
	aladdin->AddAnimation(109); //sit attack right
	aladdin->AddAnimation(-109); //sit attack left
	aladdin->AddAnimation(110); //jump attack right
	aladdin->AddAnimation(-110); //jump attack left
	aladdin->AddAnimation(111); //jump throw apple right
	aladdin->AddAnimation(-111); //jump throw apple left
	aladdin->AddAnimation(112); //climb rope
	aladdin->AddAnimation(113); //pushing right
	aladdin->AddAnimation(-113); //pushing left
	aladdin->AddAnimation(114); //dead
	aladdin->AddAnimation(115); //sit throw apple
	aladdin->AddAnimation(-115);
	aladdin->AddAnimation(119); //run attack
	aladdin->AddAnimation(-119);
	aladdin->AddAnimation(120); //run throw
	aladdin->AddAnimation(-120);
	aladdin->AddAnimation(118); //climb jump
	aladdin->AddAnimation(117); //climb attack left 
	aladdin->AddAnimation(-117); //climb attack right
	aladdin->AddAnimation(116); //climb throw left 
	aladdin->AddAnimation(-116); //climb throw right
	aladdin->AddAnimation(-121); //hurt right
	aladdin->AddAnimation(121);


	aladdin->SetPosition(100.0f, 170.f);
	objects.push_back(aladdin);
	SetSaveLocation(aladdin->x, aladdin->y);
    last_player_x = aladdin->x;
    last_player_y = aladdin->y;
#pragma endregion Initalize Aladdin

	//Initialize Boss
	boss = new Boss();
	boss->AddAnimation(BOSS_ATTACK_RIGHT);
	boss->AddAnimation(BOSS_ATTACK_LEFT);
	boss->AddAnimation(BOSS_2_ATTACK_RIGHT);
	boss->AddAnimation(BOSS_2_ATTACK_LEFT);
	boss->SetPosition(360.0f, 165.0f);
	boss->SetScene(this);
	boss->id = 1;
	objects.push_back(boss);

    ResourceLoader::GetInstance()->LoadObjectFromFile("objects_BossScene.txt", objects, 2,SCENE_BOSS);

    //Grid
    SpatialGrid* grid = SpatialGrid::GetInstance();
    grid->SetCell(500);
    grid->Clear();
    grid->AddGridFromFile(objects, "boss_scene_grid.txt");

	grid->Insert(boss);

	grid_id = objects.size();
}

void Boss_Scene::Update(DWORD dt)
{
    RECT cam_rect = camera->getBounding();
    //fix thuật toán add vào grid
    RECT temp = camera->InvertY(cam_rect.left, cam_rect.top, cam_rect.right,
        cam_rect.bottom, SCREEN_WIDTH, SCREEN_HEIGHT);

    set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(temp.left,
        temp.top, temp.right, temp.bottom);

    //Truyền set các obj thuộc các lưới va chạm với camera
    vector<LPGAMEOBJECT> coObjects(set_gameobject.begin(),
        set_gameobject.end());
	//Update objets
	objects[0]->Update(dt, &coObjects); //player
	if (aladdin->health <= 0)
		boss->hitpoint = BOSS_MAX_HITPOINT;
#pragma region
    if(aladdin->x != last_player_x)
        back->x -= aladdin->vx*dt*0.15;
    if(aladdin->y != last_player_y)
        back->y -= aladdin->vy*dt*0.08;
    last_player_x = aladdin->x;
    last_player_y = aladdin->y;
#pragma endregion Move background

	for (int i = 0; i < vector_apple.size(); i++)
	{
		vector_apple[i]->Update(dt, &coObjects);
	}
	
	for (int i = 0; i < vector_bosss_flame.size(); i++)
	{
		vector_bosss_flame[i]->Update(dt, NULL);
	}
	

	//boss
	boss->player_x = aladdin->x;
	boss->player_y = aladdin->y;

    for (int i = 0; i < coObjects.size(); i++)
    {
        if (dynamic_cast<FlameStrip*>(coObjects[i]))
        {
            if(!boss->isHumanForm)
                coObjects[i]->Update(dt, &coObjects);
        }
        else
		    coObjects[i]->Update(dt, &coObjects);
    }

#pragma region
	//Camera follow player (use distance bettween player and camera right-side)
	//Horizontally
	if (aladdin->x - camera->getPositionWorld().x > SCREEN_ACTUAL_WIDTH / 2 + 5)
	{
		camera->setPositionWorld(D3DXVECTOR2((int)(aladdin->x - SCREEN_ACTUAL_WIDTH / 2 - 5), camera->getPositionWorld().y));

		//Check right-most of the map
		if (camera->getPositionWorld().x > BOSS_MAP_WIDTH - SCREEN_ACTUAL_WIDTH)
			camera->setPositionWorld(D3DXVECTOR2(BOSS_MAP_WIDTH - SCREEN_ACTUAL_WIDTH, camera->getPositionWorld().y));
	}
	else if (aladdin->x - camera->getPositionWorld().x < SCREEN_ACTUAL_WIDTH / 2 - 5) //50 is min distance between player and left side of camera
	{
		camera->setPositionWorld(D3DXVECTOR2((int)(aladdin->x - SCREEN_ACTUAL_WIDTH / 2 + 5),
			camera->getPositionWorld().y));

		//Check left-most of the map
		if (camera->getPositionWorld().x < 0)
			camera->setPositionWorld(D3DXVECTOR2(0, camera->getPositionWorld().y));
	}
	//Vertically
	if (camera->getPositionWorld().y - aladdin->y < SCREEN_ACTUAL_HEIGHT * 1 / 4)
	{
		camera->setPositionWorld(D3DXVECTOR2(camera->getPositionWorld().x, aladdin->y + (SCREEN_ACTUAL_HEIGHT * 1 / 4)));

		//Check top-most of the map
		if (camera->getPositionWorld().y > BOSS_MAP_HEIGHT)
			camera->setPositionWorld(D3DXVECTOR2(camera->getPositionWorld().x, BOSS_MAP_HEIGHT));
	}
	else if (aladdin->y - (camera->getPositionWorld().y - SCREEN_ACTUAL_HEIGHT) < 28 + aladdin->height) // min distance between player and bottom side of camera
	{
		camera->setPositionWorld(D3DXVECTOR2((int)(camera->getPositionWorld().x), aladdin->y + SCREEN_ACTUAL_HEIGHT - (28 + aladdin->height)));
		//Check top-most of the map
		if (camera->getPositionWorld().y < SCREEN_HEIGHT)
			camera->setPositionWorld(D3DXVECTOR2(camera->getPositionWorld().x, SCREEN_HEIGHT));
	}
#pragma endregion Camera


	//delete apple throw
	for (int i = 0; i < vector_apple.size(); i++)
	{
		if (vector_apple[i]->isDead == true)
		{
			delete vector_apple[i];
			vector_apple.erase(vector_apple.begin() + i);
		}
	}

	healthHUD->HealthRatio = (float)aladdin->health / (float)MAX_HEALTH;

    if (aladdin->life <= 0)
    {
        next_scene = SCENE_MENU;
        Sound::getInstance()->stop("SCENE_BOSS");
    }
	else if (boss->hitpoint <= 0)
	{
		next_scene = SCENE_COMPLETE;
		Sound::getInstance()->stop("SCENE_BOSS");
	}
}

void Boss_Scene::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = CGame::GetInstance()->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

        back->Render();
		map->Render();

		//enemy, items, chain
		//for (int i = 1; i < objects.size(); i++)
		//{
		//	if (camera->isContain(objects[i]->x, objects[i]->y,
		//		objects[i]->x + objects[i]->width, objects[i]->y - objects[i]->height))
		//	{
		//		objects[i]->Render();
		//	}
		//}

		//vector apple
		for (int i = 0; i < vector_apple.size(); i++)
		{
			vector_apple[i]->Render();
		}

        for (int i = 1; i < objects.size(); i++)
        {
            objects[i]->Render();
        }

		//boss flame
		for (int i = 0; i < vector_bosss_flame.size(); i++)
		{
			vector_bosss_flame[i]->Render();
		}
		

		//aladdin
		objects[0]->Render();



		//Update value and position of HUD
		D3DXVECTOR2 camPos = camera->getPositionWorld();
		healthHUD->SetPosition(camPos.x + 5, camPos.y - 5);
		lifeHUD->SetPosition(camPos.x + 20, camPos.y - SCREEN_ACTUAL_HEIGHT + 20);
		rubyHUD->SetPosition(camPos.x + 240, camPos.y - SCREEN_ACTUAL_HEIGHT + 15);
		appleHUD->SetPosition(camPos.x + 300, camPos.y - SCREEN_ACTUAL_HEIGHT + 15);

		//HUD render
		healthHUD->Render();
		lifeHUD->Render();
		appleHUD->Render();
		rubyHUD->Render();

		string txt;
		txt = to_string(aladdin->score);
		DrawTextHUD(txt, camPos.x + SCREEN_ACTUAL_WIDTH - 100, camPos.y - 15, true);
		txt = to_string(aladdin->life);
		DrawTextHUD(txt, lifeHUD->x + 25, lifeHUD->y - 13);
		txt = to_string(aladdin->numRuby);
		DrawTextHUD(txt, rubyHUD->x + 20, rubyHUD->y -5);
		txt = to_string(aladdin->numApple);
		DrawTextHUD(txt, appleHUD->x + 20, appleHUD->y -5);


		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}