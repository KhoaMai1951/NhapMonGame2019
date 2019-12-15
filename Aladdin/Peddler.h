#ifndef PEDDLER_H
#define PEDDLER_H

#include "GameObject.h"

#define BBOX_WIDTH 143   //when flying
#define BBOX_HEIGHT 88
#define IDLE_TIME 3000
#define START_OPEN_SHOP_RANGE 10

enum PEDDLER_STATE
{
    PEDDLER_STATE_IDLE,
    PEDDLER_STATE_OPEN_SHOP,
};

enum PEDDLER_ANI
{
    PEDDLER_ANI_IDLE,
    PEDDLER_ANI_OPEN_SHOP,
};

class Peddler : public CGameObject
{
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
public:
    DWORD idle_start;
    Peddler() : CGameObject()
    {
        idle_start = 0;
        width = BBOX_WIDTH;
        height = BBOX_HEIGHT;
        lastFrameWidth = BBOX_WIDTH;
        lastFrameHeight = BBOX_HEIGHT;
        nx = 1;
    }
    virtual void SetState(int state);
};
#endif 