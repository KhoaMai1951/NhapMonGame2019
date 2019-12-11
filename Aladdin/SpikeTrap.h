#ifndef SPIKETRAP_H
#define SPIKETRAP_H
#include "GameObject.h"
#include "debug.h"

#define BBOX_WIDTH 49
#define BBOX_HEIGHT 35

enum SPIKETRAP_STATE
{
    STATE_DO_DAMAGE,
    STATE_NOT_DO_DAMAGE,
};

class SpikeTrap : public CGameObject
{
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

public:
    bool do_damage;
    SpikeTrap() : CGameObject()
    {
        ani = 0;
        width = BBOX_WIDTH;
        height = BBOX_HEIGHT;
    }

    virtual void SetState(int state);
};
#endif