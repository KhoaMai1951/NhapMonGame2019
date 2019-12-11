#ifndef GUARD0_H
#define GUARD0_H
#include "Enemy.h"

#define WALKING_SPEED 0.05f;

#define BBOX_WIDTH 44
#define BBOX_HEIGHT 58

enum GUARD0_STATE
{
    GUARD0_STATE_IDLE = 101,
    GUARD0_STATE_WALK = 102,
    GUARD0_STATE_ATTACK = 103,
    GUARD0_STATE_HURT = 104,
    GUARD0_STATE_DEAD = 105,
};

enum GUARD0_ANI
{
    GUARD0_ANI_IDLE_RIGHT,
    GUARD0_ANI_IDLE_LEFT,

    GUARD0_ANI_WALK_RIGHT,
    GUARD0_ANI_WALK_LEFT,

    GUARD0_ANI_ATTACK_RIGHT,
    GUARD0_ANI_ATTACK_LEFT,

    GUARD0_ANI_HURT_RIGHT,
    GUARD0_ANI_HURT_LEFT,

    GUARD0_ANI_DEAD,
};

class Guard0 : public Enemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
    DWORD idle_start;
	Guard0() : Enemy()
	{
        idle_start = 0;
		hitpoint = 2;
		score = 200;
		width = BBOX_WIDTH;
		height = BBOX_HEIGHT;
		lastFrameWidth = BBOX_WIDTH;
		lastFrameHeight = BBOX_HEIGHT;
		nx = 1;
	}
    
	virtual void SetState(int state);
};
#endif