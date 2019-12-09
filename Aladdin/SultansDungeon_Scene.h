#pragma once
#include "Scene.h"
#include "Aladdin.h"

class SultansDungeon_Scene : public Scene
{
private:
    Aladdin *aladdin;
public:
    //vector<LPGAMEOBJECT> vector_throwApples;
    SultansDungeon_Scene();
    void Update(DWORD);
    void Render();
};