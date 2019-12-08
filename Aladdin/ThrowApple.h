#pragma once
#include "GameObject.h"
#include "ViewPort.h"
#include "set"
#include "SpatialGrid.h"
#include "Apple.h"

#define THROW_APPLE_GRAVITY 0.008f;
#define THROW_APPLE_SPEED 0.015f;

enum THROW_APPLE_STATE
{
    THROW_APPLE_STATE_FLYING = 1,
    THROW_APPLE_STATE_DESTROYED = 2,
};

enum THROW_APPLE_ANI
{
    THROW_APPLE_ANI_FLYING,
    THROW_APPLE_ANI_DESTROYED,
};

enum THROW_APPLE_BOX
{
    THROW_APPLE_WIDTH = 11,
    THROW_APPLE_HEIGHT = 12,
};


class ThrowApple : public CGameObject
{
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

public:
    ThrowApple() : CGameObject()
    {
        vx = 1;
        vy = 1;
        width = THROW_APPLE_WIDTH;
        height = THROW_APPLE_HEIGHT;
    }
    virtual void SetState(int state);
};