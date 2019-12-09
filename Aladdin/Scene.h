#pragma once
#include <vector>
#include <fstream>
#include <sstream>

#include "Map.h"
#include "Game.h"
#include "ViewPort.h"
#include "Sprites.h"
#include "Textures.h"
#include "SpatialGrid.h"
#include "ResourceLoader.h"

using namespace std;

enum LEVEL
{
    SCENE_SULTAN,
    SCENE_BOSS,
    SCENE_INTRO,
    SCENE_COMPLETE
};

class Scene
{
protected:
    vector<LPGAMEOBJECT> map_vector;
    vector<LPGAMEOBJECT> front_objects;
    vector<LPGAMEOBJECT> objects; //All collision object and aladdin
    ViewPort * camera = ViewPort::getInstance();

public:
    vector<LPGAMEOBJECT> vector_throwApples;
    int next_scene;

    Scene()
    {
        next_scene = -1;
        //tile_count = 0;
    };
    virtual void Update(DWORD) {};
    virtual void Render() {};

    virtual ~Scene()
    {
        for (int i = objects.size() - 1; i >= 0; --i)
            delete objects[i];
        objects.clear();
        SpatialGrid::GetInstance()->Clear();
        for (int i = map_vector.size() - 1; i >= 0; --i)
            delete map_vector[i];

       /* CSprites* sprites = CSprites::GetInstance();
        for (int i = 0; i < tile_count; i++)
            delete (sprites->Get(TILE_INDEX + i));*/
    };
};

