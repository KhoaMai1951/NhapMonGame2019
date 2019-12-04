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
    ALADDIN_STATE_ATTACK = 107,
    ALADDIN_STATE_THROW_APPLE = 108,
    ALADDIN_STATE_SIT_ATTACK = 109,
    ALADDIN_STATE_JUMP_ATTACK = 110,
    ALADDIN_STATE_JUMP_THROW_APPLE = 111,
    ALADDIN_STATE_CLIMB = 112,
    ALADDIN_STATE_PUSH = 113,
    ALADDIN_STATE_DEAD = 114,
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

    ALADDIN_ANI_ATTACK_RIGHT,
    ALADDIN_ANI_ATTACK_LEFT,

    ALADDIN_ANI_THROW_RIGHT,
    ALADDIN_ANI_THROW_LEFT,

    ALADDIN_ANI_SIT_ATTACK_RIGHT,
    ALADDIN_ANI_SIT_ATTACK_LEFT,

    ALADDIN_ANI_JUMP_ATTACK_RIGHT,
    ALADDIN_ANI_JUMP_ATTACK_LEFT,

    ALADDIN_ANI_JUMP_THROW_RIGHT,
    ALADDIN_ANI_JUMP_THROW_LEFT,

    ALADDIN_ANI_CLIMB_ROPE,

    ALADDIN_ANI_PUSHING_RIGHT,
    ALADDIN_ANI_PUSHING_LEFT,

    ALADDIN_ANI_DEAD,
};

enum ALADDIN_BOX
{
    ALADDIN_IDLE_WIDTH = 40,
    ALADDIN_IDLE_HEIGHT = 48,

    ALADDIN_RUN_WIDTH = 41,
    ALADDIN_RUN_HEIGHT = 54,

    ALADDIN_JUMP_WIDTH = 41,
    ALADDIN_JUMP_HEIGHT = 54,

    ALADDIN_RUN_JUMP_WIDTH = 41,
    ALADDIN_RUN_JUMP_HEIGHT = 54,

    ALADDIN_LOOKUP_WIDTH = 49,    
    ALADDIN_LOOKUP_HEIGHT = 58,

    ALADDIN_CROUCH_WIDTH = 53,  
    ALADDIN_CROUCH_HEIGHT = 35,

    ALADDIN_ATTACK_WIDTH = 82,      //frame with longest width
    ALADDIN_ATTACK_HEIGHT = 70,

    ALADDIN_THROW_APPLE_WIDTH = 43,  
    ALADDIN_THROW_APPLE_HEIGHT = 56,

    ALADDIN_SIT_ATTACK_WIDTH = 92,        //frame with longest width
    ALADDIN_SIT_ATTACK_HEIGHT = 34,

    ALADDIN_JUMP_ATTACK_WIDTH = 83,         //frame with longest width
    ALADDIN_JUMP_ATTACK_HEIGHT = 60,

    ALADDIN_JUMP_THROW_APPLE_WIDTH = 39,
    ALADDIN_JUMP_THROW_APPLE_HEIGHT = 53,

    ALADDIN_CLIMB_WIDTH = 29,
    ALADDIN_CLIMB_HEIGHT = 86,

    ALADDIN_PUSH_WIDTH = 75,
    ALADDIN_PUSH_HEIGHT = 44,

    ALADDIN_DEAD_WIDTH = 55,
    ALADDIN_DEAD_HEIGHT = 52,
};


#define ALADDIN_UNTOUCHABLE_TIME 5000


class Aladdin : public CGameObject
{
    int health;
    int untouchable;
    bool jumping = false;
    DWORD untouchable_start, idle_start;

    int CheckGround0Collision(vector<LPGAMEOBJECT> *coObjects, DWORD dt);
    bool CheckGround1Collision(vector<LPGAMEOBJECT> *coObjects, DWORD dt);
    bool CheckItemCollision(vector<LPGAMEOBJECT> *coObjects, DWORD dt);

    //type: 0-ground0, 1-ground1, 2-enemies, 3-items
    /*void FilterGroundCollision0(
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
        float &ny);*/
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