#ifndef LIFEHEAL_H
#define LIFEHEAL_H
#include "GameObject.h"

#define BBOX_WIDTH 19
#define BBOX_HEIGHT 24

enum LIFEHEAL_STATE
{
    LIFEHEAL_STATE_IDLE,
    LIFEHEAL_STATE_EATEN,
};

enum LIFEHEAL_ANI
{
    LIFEHEAL_ANI_IDLE,
    LIFEHEAL_ANI_EATEN,
};

class LifeHeal : public CGameObject
{
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    virtual void Render();

public:
    LifeHeal() : CGameObject()
    {
        //lastFrameWidth = APPLE_IDLE_WIDTH;
        //lastFrameHeight = APPLE_IDLE_HEIGHT;
        isItem = true;
        width = BBOX_WIDTH;
        height = BBOX_HEIGHT;
    }
    virtual void SetState(int state);
};
#endif
