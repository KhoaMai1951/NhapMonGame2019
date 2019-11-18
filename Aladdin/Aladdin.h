#pragma once
#include "GameObject.h"
#include "ViewPort.h"
#include "Apple.h"

#define ALADDIN_RUNNING_SPEED		0.1f 
#define ALADDIN_JUMP_SPEED_Y		0.5f
#define ALADDIN_GRAVITY			0.002f

#define ALADDIN_STATE_IDLE			0
#define ALADDIN_STATE_RUNNING_RIGHT	100
#define ALADDIN_STATE_RUNNING_LEFT	200
#define ALADDIN_STATE_JUMP			300
#define ALADDIN_STATE_DIE		    400

#define ALADDIN_ANI_IDLE_RIGHT  0
#define ALADDIN_ANI_IDLE_LEFT   1

#define ALADDIN_ANI_RUNNING_RIGHT	2
#define ALADDIN_ANI_RUNNING_LEFT	3

#define ALADDIN_ANI_JUMP_RIGHT	4
#define ALADDIN_ANI_JUMP_LEFT	5

#define MARIO_ANI_DIE				999

#define ALADDIN_IDLE_WIDTH  40
#define ALADDIN_IDLE_HEIGHT 48


#define ALADDIN_UNTOUCHABLE_TIME 5000


class Aladdin : public CGameObject
{
    int health;
    int untouchable;
    bool jumping = false;
    DWORD untouchable_start;
public:
    Aladdin() : CGameObject()
    {
        health = 10;
        untouchable = 0;
        width = ALADDIN_IDLE_WIDTH;
        height = ALADDIN_IDLE_HEIGHT;
        state = ALADDIN_STATE_IDLE;
        nx = 1;
    }
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
    virtual void Render();
    void ProcessKeyboard();
    void SetState(int state);
    void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};