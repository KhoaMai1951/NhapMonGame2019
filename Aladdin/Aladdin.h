#pragma once
#include "Game.h"
#include "GameObject.h"
#include "ViewPort.h"
#include <set>
#include "SpatialGrid.h"

#include "Apple.h"
#include "Ground.h"
#include "Enemy.h"

#define ALADDIN_RUNNING_SPEED		0.15f 
#define ALADDIN_JUMP_SPEED_Y		0.3f
#define ALADDIN_GRAVITY			0.0005f

enum ALADDIN_STATE
{
    ALADDIN_STATE_IDLE = 101,
    ALADDIN_STATE_IDLE1 = 1011,
    ALADDIN_STATE_IDLE2 = 1012,
    ALADDIN_STATE_IDLE3 = 1013,
    ALADDIN_STATE_RUN = 102,
    ALADDIN_STATE_JUMP = 103,
    ALADDIN_STATE_RUN_JUMP = 104,
    ALADDIN_STATE_LOOKUP = 105,
    ALADDIN_STATE_CROUCH = 106,
    ALADDIN_STATE_DIE = 400,
};

enum ALADDIN_ANI
{
    ALADDIN_ANI_IDLE_RIGHT = 0,
    ALADDIN_ANI_IDLE_LEFT,

    ALADDIN_ANI_RUNNING_RIGHT,
    ALADDIN_ANI_RUNNING_LEFT,

    ALADDIN_ANI_JUMP_RIGHT,
    ALADDIN_ANI_JUMP_LEFT,

    ALADDIN_ANI_RUN_JUMP_RIGHT,
    ALADDIN_ANI_RUN_JUMP_LEFT,

    ALADDIN_ANI_LOOKUP_RIGHT,
    ALADDIN_ANI_LOOKUP_LEFT,

    ALADDIN_ANI_CROUCH_RIGHT,
    ALADDIN_ANI_CROUCH_LEFT,

    ALADDIN_ANI_IDLE1,
    ALADDIN_ANI_IDLE2,
    ALADDIN_ANI_IDLE3,

    ALADDIN_ANI_DIE,
};

#define ALADDIN_IDLE_WIDTH  40
#define ALADDIN_IDLE_HEIGHT 48


#define ALADDIN_UNTOUCHABLE_TIME 5000


class Aladdin : public CGameObject
{
    int health;
    int untouchable;
    bool jumping = false;
    DWORD untouchable_start, idle_start;

    //type: 0-ground0, 1-ground1, 2-enemies, 3-items
    void FilterGroundCollision0(
        vector<LPCOLLISIONEVENT> &coEvents,
        vector<LPCOLLISIONEVENT> &coEventsResult,
        float &min_tx,
        float &min_ty,
        float &nx,
        float &ny);
    void FilterGroundCollision1(
        vector<LPCOLLISIONEVENT> &coEvents,
        vector<LPCOLLISIONEVENT> &coEventsResult,
        float &min_tx,
        float &min_ty,
        float &nx,
        float &ny);
    void FilterItemCollision(
        vector<LPCOLLISIONEVENT> &coEvents,
        vector<LPCOLLISIONEVENT> &coEventsResult,
        float &min_tx,
        float &min_ty,
        float &nx,
        float &ny);
public:
    Aladdin() : CGameObject()
    {
        health = 10;
        untouchable = 0;
        idle_start = 0;
        width = ALADDIN_IDLE_WIDTH;
        height = ALADDIN_IDLE_HEIGHT;
        //state = ALADDIN_STATE_IDLE;
        SetState(ALADDIN_STATE_IDLE);
        lastFrameWidth = ALADDIN_IDLE_WIDTH;
        lastFrameHeight = ALADDIN_IDLE_HEIGHT;
        nx = 1;
    }
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
    virtual void Render();
    void ProcessKeyboard();
    void SetState(int state);
    void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};