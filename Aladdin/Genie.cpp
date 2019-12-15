#include "Genie.h"

void Genie::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    right = x + width;
    bottom = y - height;
}

void Genie::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
    CGameObject::Update(dt, coObjects);
    vy = going_up * MOVE_SPEED;

    if (y >= top_y)
        going_up = -1;
    else if (y <= bot_y)
        going_up = 1;


    if (state == GENIE_STATE_IDLE)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 3000)
        {
            SetState(GENIE_STATE_IDLE2);
        }
    }
    else if (state == GENIE_STATE_IDLE2)
    {
        if (animations[ani]->currentFrame == 4)
        {
            SetState(GENIE_STATE_IDLE);
        }
    }
    else if (state == GENIE_STATE_DEAD)
    {
        if (animations[ani]->currentFrame == 15)
        {
            isDead = true;
            return;
        }
    }

    y += vy;
}

void Genie::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case GENIE_STATE_IDLE:
        idle_start = GetTickCount();
        break;
    case GENIE_STATE_IDLE2:
        animations[GENIE_ANI_IDLE2]->ResetAnimation();
        break;
    case GENIE_STATE_DEAD:
        animations[GENIE_ANI_EXPLODE]->ResetAnimation();
        break;
    }
}

void Genie::Render()
{
    ani = GENIE_ANI_IDLE;
    if (state == GENIE_STATE_IDLE2) {
        ani = GENIE_ANI_IDLE2;
    }
    else if (state == GENIE_STATE_DEAD)
        ani = GENIE_ANI_EXPLODE;

    animations[ani]->Render(x, y);

    //RenderBoundingBox();
}