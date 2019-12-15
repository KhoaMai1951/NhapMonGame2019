#ifndef SKELETON_H
#define SKELETON_H
#include "Enemy.h"

#define BBOX_WIDTH 51
#define BBOX_HEIGHT 88

enum SKELETON_STATE
{
    SKELETON_STATE_CREATE = 101,
    SKELETON_STATE_EXPLODE = 102,
    SKELETON_STATE_DEAD = 5,
};

enum SKELETON_ANI
{
    SKELETON_ANI_CREATE,
    SKELETON_ANI_EXPLODE,
    SKELETON_ANI_DEAD,
};

class Skeleton : public Enemy
{
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

public:
    DWORD idle_start;
    Skeleton() : Enemy()
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