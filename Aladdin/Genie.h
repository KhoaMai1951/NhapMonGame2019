#pragma once
#include "GameObject.h"

#define BBOX_WIDTH 38
#define BBOX_HEIGHT 50

enum GENIE_STATE
{
    GENIE_STATE_IDLE,
    GENIE_STATE_EATEN,
};

enum GENIE_ANI
{
    GENIE_ANI_IDLE,
    GENIE_ANI_EATEN,
};

class Genie : public CGameObject
{
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    virtual void Render();

public:
    Genie() : CGameObject()
    {
        //lastFrameWidth = APPLE_IDLE_WIDTH;
        //lastFrameHeight = APPLE_IDLE_HEIGHT;
        isItem = true;
        width = BBOX_WIDTH;
        height = BBOX_HEIGHT;
    }
    virtual void SetState(int state);
};
