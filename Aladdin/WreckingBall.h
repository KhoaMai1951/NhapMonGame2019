#pragma once
#include "GameObject.h"
#include "debug.h"

#define BBOX_WIDTH 33
#define BBOX_HEIGHT 67

enum WRECKINGBALL_STATE
{
    BALL_STATE_DO_DAMAGE,
    BALL_STATE_NOT_DO_DAMAGE,
};

class WreckingBall : public CGameObject
{
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

public:
    bool do_damage;
    WreckingBall() : CGameObject()
    {
        ani = 0;
        width = BBOX_WIDTH;
        height = BBOX_HEIGHT;
    }

    virtual void SetState(int state);
};