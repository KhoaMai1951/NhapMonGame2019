#ifndef RUBY_H
#define RUBY_H
#include "GameObject.h"

#define BBOX_WIDTH 17
#define BBOX_HEIGHT 16

enum RUBY_STATE
{
    RUBY_STATE_IDLE,
    RUBY_STATE_EATEN,
};

enum RUBY_ANI
{
    RUBY_ANI_IDLE,
    RUBY_ANI_EATEN,
};

class Ruby : public CGameObject
{
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    virtual void Render();

public:
    Ruby() : CGameObject()
    {
        //lastFrameWidth = APPLE_IDLE_WIDTH;
        //lastFrameHeight = APPLE_IDLE_HEIGHT;
        isItem = true;
        scoreGain = 150;
        width = BBOX_WIDTH;
        height = BBOX_HEIGHT;
    }
    virtual void SetState(int state);
};
#endif
