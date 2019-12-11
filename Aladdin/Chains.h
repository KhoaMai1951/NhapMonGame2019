#ifndef CHAINS_H
#define CHAINS_H
#include "GameObject.h"
#include "debug.h"

enum CHAINS_STATE
{
    CHAINS_STATE_IDLE,
};

class Chains : public CGameObject
{
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

public:
	float bot;
    Chains() : CGameObject()
    {
        ani = 0;
    }

    virtual void SetState(int state);
};
#endif