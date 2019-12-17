#ifndef GUARD1_H
#define GUARD1_H
#include "Enemy.h"

#define WALKING_SPEED 0.05f

#define BBOX_WIDTH 55
#define BBOX_HEIGHT 52
#define GUARD1_ATTACK1_SIZE 40
#define GUARD1_ATTACK2_SIZE 59
#define GUARD1_TAUNT_SIZE 180
#define TAUNT_DELAY_TIME 2000
#define GUARD1_ATTACK_DELAY_TIME 2000
#define UNDER_ABOVE_ATTACK_RANGE 100

enum GUARD1_STATE
{
    GUARD1_STATE_IDLE = 101,
    GUARD1_STATE_WALK = 102,
    GUARD1_STATE_TAUNT = 103,
    GUARD1_STATE_ATTACK1 = 104,
    GUARD1_STATE_ATTACK2 = 105,
    GUARD1_STATE_HURT = 4,
    GUARD1_STATE_DEAD = 5,
};

enum GUARD1_ANI
{
    GUARD1_ANI_IDLE_RIGHT = 0,
    GUARD1_ANI_IDLE_LEFT,

    GUARD1_ANI_WALK_RIGHT,
    GUARD1_ANI_WALK_LEFT,

    GUARD1_ANI_TAUNT_RIGHT,
    GUARD1_ANI_TAUNT_LEFT,

    GUARD1_ANI_ATTACK1_RIGHT,
    GUARD1_ANI_ATTACK1_LEFT,

    GUARD1_ANI_ATTACK2_RIGHT,
    GUARD1_ANI_ATTACK2_LEFT,

    GUARD1_ANI_HURT_RIGHT,
    GUARD1_ANI_HURT_LEFT,

    GUARD1_ANI_DEAD,
};

class Guard1 : public Enemy
{
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

public:
    DWORD idle_start;
    Guard1() : Enemy()
    {
        idle_start = 0;
        hitpoint = 2;
        scoreGain = 100;
        width = BBOX_WIDTH;
        height = BBOX_HEIGHT;
        lastFrameWidth = BBOX_WIDTH;
        lastFrameHeight = BBOX_HEIGHT;
        nx = 1;
    }

    virtual void SetState(int state);
};
#endif