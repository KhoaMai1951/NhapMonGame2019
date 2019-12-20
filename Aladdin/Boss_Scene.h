#ifndef Boss_Scene_H
#define Boss_Scene_H
#include "Scene.h"
class Boss_Scene : public Scene
{
private:
    DWORD generate_start = GetTickCount();
public:
	vector<CGameObject*> vector_apple;
    CMap *map, *back;
	Boss* boss;
	vector<CGameObject*> vector_boss_flame;
    vector<CGameObject*> vector_boss_spell;
    vector<CGameObject*> vector_generate_apple;
    D3DXVECTOR2 apple_location[8]
    { D3DXVECTOR2(262.25,270.75),
    D3DXVECTOR2(280.5,280.75),
    D3DXVECTOR2(280.5,259.25),
    D3DXVECTOR2(298.25,270.75),
    D3DXVECTOR2(528.5,270.75),
    D3DXVECTOR2(546.75,280.75),
    D3DXVECTOR2(546.75,259.25),
    D3DXVECTOR2(564.5,270.75) };
    float last_player_x, last_player_y;
	int grid_id;
	Boss_Scene();
	void Update(DWORD);
	void Render();
	void Initialize();
};
#endif