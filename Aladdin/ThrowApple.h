#ifndef THROWAPPLE_H
#define THROWAPPLE_H
#include "GameObject.h"
#include "ViewPort.h"
#include "set"
#include "SpatialGrid.h"
#include "Enemy.h"
#include "Ground.h"

#define THROW_APPLE_GRAVITY 0.003f
#define THROW_APPLE_SPEED 0.28f

#define THROW_APPLE_BBOX_SIZE 9


enum THROW_APPLE_STATE
{
    THROW_APPLE_STATE_FLYING,
    THROW_APPLE_STATE_DESTROYED,
};

enum THROW_APPLE_ANI
{
    THROW_APPLE_ANI_FLYING_RIGHT,
    THROW_APPLE_ANI_FLYING_LEFT,
    THROW_APPLE_ANI_DESTROYED,
};


class ThrowApple : public CGameObject
{
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

public:
    ThrowApple() : CGameObject()
    {
        vx = 0;
        vy = 0;
        width = THROW_APPLE_BBOX_SIZE;
        height = THROW_APPLE_BBOX_SIZE;
    }
    virtual void SetState(int state);
};
#endif