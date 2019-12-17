#ifndef GENIE_H
#define GENIE_H
#include "GameObject.h"

#define BBOX_WIDTH 38
#define BBOX_HEIGHT 50
#define MOVE_DISTANCE 3
#define MOVE_SPEED 0.2f

enum GENIE_STATE
{
    GENIE_STATE_IDLE,
    GENIE_STATE_IDLE2,
    GENIE_STATE_DEAD = 5,
};

enum GENIE_ANI
{
    GENIE_ANI_IDLE,
    GENIE_ANI_IDLE2,
    GENIE_ANI_EXPLODE,
};

class Genie : public CGameObject
{
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    virtual void Render();
    DWORD idle_start;
    int going_up = 1;
    float top_y, bot_y; //for move up and down
public:
    
    Genie() : CGameObject()
    {
        idle_start = 0;
        //lastFrameWidth = APPLE_IDLE_WIDTH;
        //lastFrameHeight = APPLE_IDLE_HEIGHT;
        scoreGain = 200;
        isItem = true;
        width = BBOX_WIDTH;
        height = BBOX_HEIGHT;
    }

    void GetMoveLimit()
    {
        top_y = y + MOVE_DISTANCE;
        bot_y = y - MOVE_DISTANCE;
    }

    virtual void SetState(int state);
};
#endif
