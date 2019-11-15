#include "SultansDungeon_Scene.h"

SultansDungeon_Scene::SultansDungeon_Scene()
{
    ResourceLoader::GetInstance()->LoadMapFromFile("Map_Background.txt", CTextures::GetInstance()->Get(ID_TEX_MAP), map_vector);

    mario = new CMario();
    mario->AddAnimation(400);		// idle right big
    mario->AddAnimation(401);		// idle left big
    mario->AddAnimation(402);		// idle right small
    mario->AddAnimation(403);		// idle left small

    mario->AddAnimation(500);		// walk right big
    mario->AddAnimation(501);		// walk left big
    mario->AddAnimation(502);		// walk right small
    mario->AddAnimation(503);		// walk left big

    mario->AddAnimation(599);		// die

    mario->SetPosition(50.0f, 100);
    objects.push_back(mario);

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

    set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(cam_rect.left, cam_rect.top, cam_rect.right, cam_rect.bottom);

    //Truyền set các obj thuộc các lưới có player vào vector
    vector<LPGAMEOBJECT> coObjects(set_gameobject.begin(), set_gameobject.end()); //Vector chứa các Object va chạm (trừ index 0 vì là Mario)

    //Update objects
    objects[0]->Update(dt, &coObjects); //player
    for (int i = 0; i < coObjects.size(); i++)
    {
        coObjects[i]->Update(dt, &coObjects);
    }

    //Camera follow player (use distance bettween player and camera right-side)
    //Horizontally
    if (mario->x - camera->getPositionWorld().x > SCREEN_WIDTH / 2)
    {
    	/*camera->setPositionWorld(D3DXVECTOR2((int)(this->x - SCREEN_WIDTH / 2),
    		camera->getPositionWorld().y));*/
    	camera->setPositionWorld(D3DXVECTOR2((int)(mario->x - SCREEN_WIDTH / 2), 
            camera->getPositionWorld().y));
    }
    else if (mario->x - camera->getPositionWorld().x < 50) //50 is min distance between player and left side of camera
    {
    	/*camera->setPositionWorld(D3DXVECTOR2((int)(this->x - 50),
    		camera->getPositionWorld().y));*/
    	camera->setPositionWorld(D3DXVECTOR2((int)(mario->x - 50),
            camera->getPositionWorld().y));
    }
    //Vertically
   /* if (camera->getPositionWorld().y - mario->y > SCREEN_ACTUAL_HEIGHT * 3/4)
    {
        camera->setPositionWorld(D3DXVECTOR2((int)(camera->getPositionWorld().x),
            mario->y + (SCREEN_ACTUAL_HEIGHT * 3 / 4)));
    }*/
    //else if (mario->y - camera->getPositionWorld().y - SCREEN_HEIGHT < 5) //5 is min distance between player and bottom side of camera
    //{
    //    camera->setPositionWorld(D3DXVECTOR2((int)(camera->getPositionWorld().x),
    //        mario->y - 5));
    //}

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

        spriteHandler->End();
        d3ddv->EndScene();
    }

    // Display back buffer content to the screen
    d3ddv->Present(NULL, NULL, NULL, NULL);
}