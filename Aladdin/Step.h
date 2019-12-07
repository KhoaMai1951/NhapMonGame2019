#pragma once
#include "GameObject.h"
#include "debug.h"

#define BBOX_WIDTH 40
#define BBOX_HEIGHT 24

enum STEP_STATE
{
    STATE_STANDABLE,
    STATE_NOT_STANDABLE,
};

class Step : public CGameObject
{
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

public:
    bool standable;
    Step() : CGameObject()
    {
        ani = 0;
        width = BBOX_WIDTH;
        height = BBOX_HEIGHT;
    }

    virtual void SetState(int state);
};