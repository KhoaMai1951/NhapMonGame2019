#ifndef Boss_Scene_H
#define Boss_Scene_H
#include "Scene.h"
class Boss_Scene : public Scene
{
private:

public:
	vector<CGameObject*> vector_apple;
    CMap *map, *back;
	Boss* boss;
	vector<CGameObject*> vector_bosss_flame;
    float last_player_x, last_player_y;
	int grid_id;
	Boss_Scene();
	void Update(DWORD);
	void Render();
	void Initialize();
};
#endif