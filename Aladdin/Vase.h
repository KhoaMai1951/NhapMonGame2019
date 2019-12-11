#ifndef VASE_H
#define VASE_H
#include "GameObject.h"

#define BBOX_WIDTH 20
#define BBOX_HEIGHT 33

enum VASE_STATE
{
    VASE_STATE_IDLE,
    VASE_STATE_EATEN,
};

enum VASE_ANI
{
    VASE_ANI_IDLE,
    VASE_ANI_EATEN,
};

class Vase : public CGameObject
{
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    virtual void Render();

public:
    Vase() : CGameObject()
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
