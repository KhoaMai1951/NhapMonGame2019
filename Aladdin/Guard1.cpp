#include "Guard1.h"
void Guard1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    //width = lastFrameWidth;
    height = lastFrameHeight;

    left = x;
    top = y;
    right = left + width;
    bottom = top - height;
    /*switch (state)
    {
    case STATE_IDLE:
        right = x + BBOX_WIDTH;
        bottom = y - BBOX_HEIGHT;
        break;
    default:
        right = x + BBOX_WIDTH;
        bottom = y - BBOX_HEIGHT;
    }*/
}

void Guard1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);
    x += dx;
    y += dy;

    if (state == GUARD1_STATE_IDLE)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 1000)
        {
            SetState(GUARD1_STATE_WALK);
        }
    }
    else if (state == GUARD1_STATE_WALK)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 3000)
        {
            SetState(GUARD1_STATE_TAUNT);
        }
    }
    else if (state == GUARD1_STATE_TAUNT)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 5000)
        {
            SetState(GUARD1_STATE_ATTACK1);
        }
    }
    else if (state == GUARD1_STATE_ATTACK1)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 7000)
        {
            SetState(GUARD1_STATE_ATTACK2);
        }
    }
    else if (state == GUARD1_STATE_ATTACK2)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 9000)
        {
            SetState(GUARD1_STATE_HURT);
        }
    }
    else if (state == GUARD1_STATE_HURT)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 11000)
        {
            SetState(GUARD1_STATE_DEAD);
        }
    }
    else if (state == GUARD1_STATE_DEAD)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 12000)
        {
            SetState(GUARD1_STATE_IDLE);
            nx = -nx;
        }
    }

}

void Guard1::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case GUARD1_STATE_IDLE:
        idle_start = GetTickCount();
        break;
    case GUARD1_STATE_WALK:
        animations[GUARD1_ANI_WALK_LEFT]->ResetAnimation();
        animations[GUARD1_ANI_WALK_RIGHT]->ResetAnimation();
        break;
    case GUARD1_STATE_TAUNT:
        animations[GUARD1_ANI_TAUNT_LEFT]->ResetAnimation();
        animations[GUARD1_ANI_TAUNT_RIGHT]->ResetAnimation();
        break;
    case GUARD1_STATE_ATTACK1:
        animations[GUARD1_ANI_ATTACK1_LEFT]->ResetAnimation();
        animations[GUARD1_ANI_ATTACK1_RIGHT]->ResetAnimation();
        break;
    case GUARD1_STATE_ATTACK2:
        animations[GUARD1_ANI_ATTACK2_LEFT]->ResetAnimation();
        animations[GUARD1_ANI_ATTACK2_RIGHT]->ResetAnimation();
        break;
    case GUARD1_STATE_HURT:
        animations[GUARD1_ANI_HURT_LEFT]->ResetAnimation();
        animations[GUARD1_ANI_HURT_RIGHT]->ResetAnimation();
        break;
    case GUARD1_STATE_DEAD:
        animations[GUARD1_ANI_DEAD]->ResetAnimation();
        break;
    }
}

void Guard1::Render()
{
    int restart_frame = 0;
    switch (state)
    {
    case GUARD1_STATE::GUARD1_STATE_IDLE:
    {
        restart_frame = 0;
        if (nx > 0)
            ani = GUARD1_ANI_IDLE_RIGHT;
        else
            ani = GUARD1_ANI_IDLE_LEFT;
        break;
    }
    case GUARD1_STATE::GUARD1_STATE_WALK:
    {
        restart_frame = 0;
        if (nx > 0)
            ani = GUARD1_ANI_WALK_RIGHT;
        else if (vx < 0)
            ani = GUARD1_ANI_WALK_LEFT;
        break;
    }
    case GUARD1_STATE::GUARD1_STATE_TAUNT:
    {
        restart_frame = 0;
        if (nx > 0)
            ani = GUARD1_ANI_TAUNT_RIGHT;
        else
            ani = GUARD1_ANI_TAUNT_LEFT;
        break;
    }
    case GUARD1_STATE::GUARD1_STATE_ATTACK1:
    {
        restart_frame = 0;
        if (nx > 0)
            ani = GUARD1_ANI_ATTACK1_RIGHT;
        else if (nx < 0)
            ani = GUARD1_ANI_ATTACK1_LEFT;
        break;
    }
    case GUARD1_STATE::GUARD1_STATE_ATTACK2:
    {
        restart_frame = 0;
        if (nx > 0)
            ani = GUARD1_ANI_ATTACK2_RIGHT;
        else if (nx < 0)
            ani = GUARD1_ANI_ATTACK2_LEFT;
        break;
    }
    case GUARD1_STATE::GUARD1_STATE_HURT:
    {
        restart_frame = 0;
        if (nx > 0)
            ani = GUARD1_ANI_HURT_RIGHT;
        else if (nx < 0)
            ani = GUARD1_ANI_HURT_LEFT;
        break;
    }
    case GUARD1_STATE::GUARD1_STATE_DEAD:
    {
        restart_frame = 0;
        ani = GUARD1_ANI_DEAD;
        break;
    }
    default:
        restart_frame = 0;
        if (nx > 0)
            ani = GUARD1_ANI_IDLE_RIGHT;
        else
            ani = GUARD1_ANI_IDLE_LEFT;
    }

    int alpha = 255;
    //animations[ani]->Render(x, y, alpha, restart_frame);
    animations[ani]->Render(x, y, width, lastFrameHeight, alpha, restart_frame, nx);

    RenderBoundingBox();
}