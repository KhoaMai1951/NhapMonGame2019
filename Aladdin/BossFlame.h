#ifndef BOSSFLAME_H
#define BOSSFLAME_H

#include "set"
#include "SpatialGrid.h"
#include "Enemy.h"
#include "Ground.h"
#include "debug.h"


#define BOSS_FLAME_SPEED 0.10f


enum BossFlameState {
	
};

enum BossFlameAni
{
	BOSS_FLAME_ANI_RUNNING_RIGHT,
	BOSS_FLAME_ANI_RUNNING_LEFT,
};

enum BossFlameSize {
	BOSS_FLAME_WIDTH = 101,
	BOSS_FLAME_HEIGHT = 53,
};

class BossFlame : public Enemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	DWORD create_start;

public:
	BossFlame() : Enemy()
	{
		create_start = GetTickCount();
		vx = 0;
		vy = -1;
		hitpoint = 1;
		width = BOSS_FLAME_WIDTH;
		height = BOSS_FLAME_HEIGHT;
	}
	virtual void SetState(int state);
	void InsertToGrid() { SpatialGrid::GetInstance()->Insert(this); }
};

#endif // ! BONE_H