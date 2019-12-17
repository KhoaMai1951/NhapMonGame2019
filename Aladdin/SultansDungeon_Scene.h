#ifndef SultansDungeon_Scene_H
#define SultansDungeon_Scene_H
#include "Scene.h"
class SultansDungeon_Scene : public Scene
{
private:

public:
    vector<CGameObject*> vector_apple;
    vector<CGameObject*> vector_environment;
    vector<CGameObject*> All_collide_objects;
	vector<CGameObject*> vector_bone;
    int grid_id;
    SultansDungeon_Scene();
    void Update(DWORD);
    void Render();
    void Initialize();
};
#endif