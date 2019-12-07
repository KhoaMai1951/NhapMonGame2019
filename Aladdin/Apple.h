#pragma once
#include "GameObject.h"
#include "ViewPort.h"
#include "set"
#include "SpatialGrid.h"
#include "Aladdin.h"

#define APPLE_IDLE_WIDTH 11
#define APPLE_IDLE_HEIGHT 12

#define APPLE_DESTROY_WIDTH 8
#define APPLE_DESTROY_HEIGHT 9

#define APPLE_STATE_IDLE 100
#define APPLE_STATE_DESTROY 200

#define APPLE_ANI_IDLE 0
#define APPLE_ANI_DESTROY 1

class Apple : public CGameObject
{
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    virtual void Render();

public:
    Apple() : CGameObject()
    {
        isItem = true;
        lastFrameWidth = APPLE_IDLE_WIDTH;
        lastFrameHeight = APPLE_IDLE_HEIGHT;
    }
    virtual void SetState(int state);
};