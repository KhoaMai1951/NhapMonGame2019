#include "SultansDungeon_Scene.h"

SultansDungeon_Scene::SultansDungeon_Scene()
{
    ResourceLoader::GetInstance()->LoadMapFromFile("Map_Background.txt", CTextures::GetInstance()->Get(TEX_MAP_DUNGEON), map_vector);
    ResourceLoader::GetInstance()->LoadObjectFromFile("Map_Front_Dungeon.txt", front_objects);
#pragma region 
    aladdin = new Aladdin();
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

    aladdin->SetPosition(100.0f, 150.f);
    objects.push_back(aladdin);
#pragma endregion Initalize Aladdin

    ResourceLoader::GetInstance()->LoadObjectFromFile("test2.txt", objects);

    SpatialGrid::GetInstance()->SetCell(CELL_SIZE);

};

void SultansDungeon_Scene::Update(DWORD dt)
{
    // We know that Mario is the first object in the list hence we won't add him into the colliable object list

    /*for (int i = 1; i < objects.size(); i++)
    {
        coObjects.push_back(objects[i]);
    }*/ 

    //Grid
    SpatialGrid* grid = SpatialGrid::GetInstance();
    grid->Clear();
    for (unsigned i = 1; i < objects.size(); i++)
        grid->Insert(objects[i]);
    
    RECT cam_rect = camera->getBounding();

   /* set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(cam_rect.left, 
		cam_rect.top, cam_rect.right, cam_rect.bottom);*/

	//set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(mario->x,
	//	mario->y, mario->x + mario->width, mario->y - mario->height);

	//set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(200,150,3000,10);
	RECT temp = camera->InvertY(cam_rect.left, cam_rect.top, cam_rect.right, 
		cam_rect.bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
	set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(temp.left, 
		temp.top, temp.right, temp.bottom);

    //Truyền set các obj thuộc các lưới có player vào vector
    vector<LPGAMEOBJECT> coObjects(set_gameobject.begin(), 
		set_gameobject.end()); //Vector chứa các Object va chạm (trừ index 0 vì là player)

    //Update objects
    objects[0]->Update(dt, &coObjects); //player

    for (int i = 0; i < coObjects.size(); i++)
    {
        coObjects[i]->Update(dt, &coObjects);
    }

#pragma region
    //Camera follow player (use distance bettween player and camera right-side)
    //Horizontally
    if (aladdin->x - camera->getPositionWorld().x > SCREEN_ACTUAL_WIDTH / 2)
    {
    	camera->setPositionWorld(D3DXVECTOR2((int)(aladdin->x - SCREEN_ACTUAL_WIDTH / 2),  camera->getPositionWorld().y));

        //Check right-most of the map
        if (camera->getPositionWorld().x > MAP_WIDTH - SCREEN_ACTUAL_WIDTH)
            camera->setPositionWorld(D3DXVECTOR2(MAP_WIDTH - SCREEN_ACTUAL_WIDTH, camera->getPositionWorld().y));
    }
    else if (aladdin->x - camera->getPositionWorld().x < 50) //50 is min distance between player and left side of camera
    {
    	camera->setPositionWorld(D3DXVECTOR2((int)(aladdin->x - 50),
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

    for (int i = objects.size() - 1; i >= 0; --i)
        if (objects[i]->isDead)
        {
            delete objects[i];
            objects.erase(objects.begin() + i);
        }

 /*   if (mario->x > MAP_WIDTH)
        next_scene = SCENE_COMPLETE;
    else if (mario->HP == 0)
        next_scene = SCENE_SULTAN;*/
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

        for (int i = 0; i < objects.size(); i++)
            objects[i]->Render();

        for (int i = 0; i < front_objects.size(); i++)
        {
            //IsContain(left, top, right, bottom) truyền vào l,t,r,b của object và xem có overlap với camera hay ko
            if (camera->isContain(front_objects[i]->x, front_objects[i]->y,
                front_objects[i]->x + front_objects[i]->width, front_objects[i]->y - front_objects[i]->height))
            {
                front_objects[i]->Render();
            }

        }

        spriteHandler->End();
        d3ddv->EndScene();
    }

    // Display back buffer content to the screen
    d3ddv->Present(NULL, NULL, NULL, NULL);
}