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

#define ALADDIN_STATE_IDLE	    101
#define ALADDIN_STATE_RUN	    102
#define ALADDIN_STATE_JUMP		103
#define ALADDIN_STATE_RUN_JUMP  104
#define ALADDIN_STATE_LOOKUP  105
#define ALADDIN_STATE_CROUCH  106
#define ALADDIN_STATE_DIE		400

#define ALADDIN_ANI_IDLE_RIGHT  0
#define ALADDIN_ANI_IDLE_LEFT   1

#define ALADDIN_ANI_RUNNING_RIGHT	2
#define ALADDIN_ANI_RUNNING_LEFT	3

#define ALADDIN_ANI_JUMP_RIGHT	4
#define ALADDIN_ANI_JUMP_LEFT	5

#define ALADDIN_ANI_RUN_JUMP_RIGHT	6
#define ALADDIN_ANI_RUN_JUMP_LEFT	7

#define ALADDIN_ANI_LOOKUP_RIGHT	8
#define ALADDIN_ANI_LOOKUP_LEFT 	9

#define ALADDIN_ANI_CROUCH_RIGHT	10
#define ALADDIN_ANI_CROUCH_LEFT	    11

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

    vector<CCollisionEvent*> GetWallCollision(vector<CCollisionEvent*>&, float&, float&, float&, float&);
    vector<CCollisionEvent*> GetEnemyCollision(vector<CCollisionEvent*>&);
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