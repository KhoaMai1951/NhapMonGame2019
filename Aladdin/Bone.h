#ifndef  BONE_H
#define BONE_H

#include "set"
#include "SpatialGrid.h"
#include "Enemy.h"
#include "Ground.h"
#include "debug.h"


#define BONE_GRAVITY 0.0015f
#define BONE_SPEED 0.0025f
#define AUTO_DESTROY_TIME 2000

enum BoneState {
    BONE_STATE_FLYING = 0,
    BONE_STATE_DEAD = 5,
};

enum BoneAni
{
	BONE_ANI_FLYING,
    BONE_ANI_DEAD,
};

enum BoneBoxSize {
	BONE_WIDTH = 16,
	BONE_HEIGHT = 15,
};

class Bone : public Enemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	DWORD create_start;

public:
	Bone() : Enemy()
	{
		create_start = GetTickCount();
		vx = 0;
		vy = -1;
		hitpoint = 1;
		width = BONE_WIDTH;
		height = BONE_HEIGHT;
        scoreGain = 150;
	}
	virtual void SetState(int state);
    void InsertToGrid() { SpatialGrid::GetInstance()->Insert(this); }
};

#endif // ! BONE_H