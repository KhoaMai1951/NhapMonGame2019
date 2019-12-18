#include "SultansDungeon_Scene.h"

SultansDungeon_Scene::SultansDungeon_Scene()
{

};

void SultansDungeon_Scene::Initialize()
{
    ViewPort::getInstance()->setPositionWorld(D3DXVECTOR2(0, SCREEN_HEIGHT));
	Sound::getInstance()->play("SCENE_SULTAN_SOUND", true, 0);

    ResourceLoader::GetInstance()->LoadObjectFromFile("Map_Front_Dungeon.txt", front_objects);

    //----------Load Map từ file text và Tile Set
    CTextures* textures = CTextures::GetInstance();

    textures->Add(TEX_TILESET_DUNGEON, L"textures\\TileSet_Sultans Dungeon_Back.png", D3DCOLOR_XRGB(255, 255, 255));

    LPDIRECT3DTEXTURE9 texDungeonTileSet = textures->Get(TEX_TILESET_DUNGEON);

    ResourceLoader::GetInstance()->load_tile_map(texDungeonTileSet, "Map_Matrix_Dungeon.txt", map_vector);
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


    aladdin->SetPosition(100.0f, 150.f);
    objects.push_back(aladdin);
    SetSaveLocation(aladdin->x, aladdin->y);
#pragma endregion Initalize Aladdin vector_environment

    ResourceLoader::GetInstance()->LoadObjectFromFile("test2.txt", objects, 1);
	//Truyền scene vào skeleton
	for (int i = 1; i < objects.size(); i++)
	{
		if (dynamic_cast<Skeleton*>(objects[i]))
			dynamic_cast<Skeleton*>(objects[i])->SetScene(this);
	}
    ResourceLoader::GetInstance()->LoadObjectFromFile("Map_Environment_Dungeon.txt", vector_environment, objects.size());
    
    for (int i = 0; i < objects.size(); i++)
        All_collide_objects.push_back(objects[i]);

    for (int i = 0; i < vector_environment.size(); i++)
    {
        All_collide_objects.push_back(vector_environment[i]);
    }

    grid_id = All_collide_objects.size();
	
    SpatialGrid::GetInstance()->SetCell(CELL_SIZE);

    //Grid
    SpatialGrid* grid = SpatialGrid::GetInstance();
    grid->Clear();
    //for (unsigned i = 1; i < objects.size(); i++)
        //grid->Insert(objects[i]);
    grid->AddGridFromFile(All_collide_objects, "dungeon_grid.txt");
}

void SultansDungeon_Scene::Update(DWORD dt)
{   
    RECT cam_rect = camera->getBounding();
	//fix thuật toán add vào grid
	RECT temp = camera->InvertY(cam_rect.left, cam_rect.top, cam_rect.right, 
		cam_rect.bottom, SCREEN_WIDTH, SCREEN_HEIGHT);

	set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(temp.left, 
		temp.top, temp.right, temp.bottom);

    //Truyền set các obj thuộc các lưới va chạm với camera
    vector<LPGAMEOBJECT> coObjects(set_gameobject.begin(), 
		set_gameobject.end()); //Vector chứa các Object va chạm (trừ index 0 vì là player)

	SpatialGrid* grid = SpatialGrid::GetInstance();
    //Update objets
    objects[0]->Update(dt, &coObjects); //player
    for (int i = 0; i < coObjects.size(); i++)
    {
        if (coObjects[i] != NULL)
        {
            if (!coObjects[i]->isItem)
            {
                coObjects[i]->player_x = aladdin->x;
                coObjects[i]->player_y = aladdin->y;
            }
            coObjects[i]->Update(dt, &coObjects);
        }
    }
    for (int i = 0; i < vector_apple.size(); i++)
    {
        vector_apple[i]->Update(dt, &coObjects);
    }
    for (int i = 0; i < vector_bone.size(); i++)
    {
        vector_bone[i]->Update(dt, NULL);
    }
    for (int i = 0; i < vector_environment.size(); i++)
    {
        vector_environment[i]->Update(dt, NULL);
    }

#pragma region
    //Camera follow player (use distance bettween player and camera right-side)
    //Horizontally
    if (aladdin->x - camera->getPositionWorld().x > SCREEN_ACTUAL_WIDTH / 2 + 5)
    {
    	camera->setPositionWorld(D3DXVECTOR2((int)(aladdin->x - SCREEN_ACTUAL_WIDTH / 2 - 5),  camera->getPositionWorld().y));

        //Check right-most of the map
        if (camera->getPositionWorld().x > MAP_WIDTH - SCREEN_ACTUAL_WIDTH)
            camera->setPositionWorld(D3DXVECTOR2(MAP_WIDTH - SCREEN_ACTUAL_WIDTH, camera->getPositionWorld().y));
    }
    else if (aladdin->x - camera->getPositionWorld().x < SCREEN_ACTUAL_WIDTH / 2 - 5) //50 is min distance between player and left side of camera
    {
    	camera->setPositionWorld(D3DXVECTOR2((int)(aladdin->x - SCREEN_ACTUAL_WIDTH / 2 + 5),
            camera->getPositionWorld().y));

        //Check left-most of the map
        if(camera->getPositionWorld().x < 0)
            camera->setPositionWorld(D3DXVECTOR2(0, camera->getPositionWorld().y));
    }
    //Vertically
    if (camera->getPositionWorld().y - aladdin->y < SCREEN_ACTUAL_HEIGHT * 1 / 4)
    {
         camera->setPositionWorld(D3DXVECTOR2(camera->getPositionWorld().x, aladdin->y + (SCREEN_ACTUAL_HEIGHT * 1 / 4)));

        //Check top-most of the map
         if (camera->getPositionWorld().y > MAP_HEIGHT)
              camera->setPositionWorld(D3DXVECTOR2(camera->getPositionWorld().x, MAP_HEIGHT));
    }
    else if (aladdin->y - (camera->getPositionWorld().y - SCREEN_ACTUAL_HEIGHT) < 28 + aladdin->height) // min distance between player and bottom side of camera
    {
        camera->setPositionWorld(D3DXVECTOR2((int)(camera->getPositionWorld().x), aladdin->y + SCREEN_ACTUAL_HEIGHT - (28 + aladdin->height)));
        //Check top-most of the map
         if (camera->getPositionWorld().y < SCREEN_HEIGHT)
              camera->setPositionWorld(D3DXVECTOR2(camera->getPositionWorld().x, SCREEN_HEIGHT));
    }
#pragma endregion Camera

   // for (int i = 0; i < objects.size(); i++)
   //     if (objects[i]->isDead)
   //     {
			////delete in grid
			//SpatialGrid::GetInstance()->DeleteFromGrid(objects[i]->id);

			////delete in objects
   //         
			//delete objects[i];
   //         objects[i] = NULL;
			//objects.erase(objects.begin() + i);
   //         All_collide_objects.erase(All_collide_objects.begin() + i);
   //     }
    //delete apple throw
    for (int i = 0; i < vector_apple.size(); i++)
    {
        if (vector_apple[i]->isDead == true)
        {
            delete vector_apple[i];
            vector_apple.erase(vector_apple.begin() + i);  
        }
    }
	//delete bone
	//for (int i = vector_bone.size() - 1; i >= 0 ; --i)
	//{
	//	if (vector_bone[i]->isDead == true)
	//	{
 //           SpatialGrid::GetInstance()->DeleteFromGrid(vector_bone[i]->id);
	//		delete vector_bone[i];
 //           vector_bone[i] = NULL;
	//		vector_bone.erase(vector_bone.begin() + i);
	//	}
	//}

	healthHUD->HealthRatio = (float)aladdin->health / (float)MAX_HEALTH;
    if (aladdin->x > MAP_WIDTH)
    {
        next_scene = SCENE_COMPLETE;
        Sound::getInstance()->stop("SCENE_SULTAN_SOUND");
    }    
    else if (aladdin->life < 0)
    {
        next_scene = SCENE_MENU;
        Sound::getInstance()->stop("SCENE_SULTAN_SOUND");
    }    
}

void SultansDungeon_Scene::Render()
{
    LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
    LPDIRECT3DSURFACE9 bb = CGame::GetInstance()->GetBackBuffer();
    LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

    if (d3ddv->BeginScene())
    {
        // Clear back buffer with a color
        d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

        spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

        for (int i = 0; i < map_vector.size(); i++)
        {
            //IsContain(left, top, right, bottom) truyền vào l,t,r,b của object và xem có overlap với camera hay ko
            if (camera->isContain(map_vector[i]->x, map_vector[i]->y,
                map_vector[i]->x + map_vector[i]->width, map_vector[i]->y - map_vector[i]->height))
            {
                map_vector[i]->Render();
            }

        }
		//step, spike, ball
        for (int i = 0; i < vector_environment.size(); i++)
        {
            vector_environment[i]->Render();
        }
		//enemy, items, chain
        for (int i = 1; i < objects.size(); i++)
        {
            if (camera->isContain(objects[i]->x, objects[i]->y,
                objects[i]->x + objects[i]->width, objects[i]->y - objects[i]->height))
            {
                objects[i]->Render();
            }
        }
		//bone
		for (int i = 0; i < vector_bone.size(); i++)
		{
			vector_bone[i]->Render();
		}

		//aladdin
        objects[0]->Render();

		//vector apple
        for (int i = 0; i < vector_apple.size(); i++)
        {
            vector_apple[i]->Render();
        }


        for (int i = 0; i < front_objects.size(); i++)
        {
            //IsContain(left, top, right, bottom) truyền vào l,t,r,b của object và xem có overlap với camera hay ko
            if (camera->isContain(front_objects[i]->x, front_objects[i]->y,
                front_objects[i]->x + front_objects[i]->width, front_objects[i]->y - front_objects[i]->height))
            {
                front_objects[i]->Render();
            }

        }

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
		DrawTextHUD(txt, camPos.x + SCREEN_ACTUAL_WIDTH - 100, camPos.y - 15);
		txt = to_string(aladdin->life);
		DrawTextHUD(txt, lifeHUD->x + 25, lifeHUD->y - 5);
		txt = to_string(aladdin->numRuby);
		DrawTextHUD(txt, rubyHUD->x + 20, rubyHUD->y);
		txt = to_string(aladdin->numApple);
		DrawTextHUD(txt, appleHUD->x + 20, appleHUD->y);


        spriteHandler->End();
        d3ddv->EndScene();
    }

    // Display back buffer content to the screen
    d3ddv->Present(NULL, NULL, NULL, NULL);
}