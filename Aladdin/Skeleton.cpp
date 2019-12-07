#include "Skeleton.h"
void Skeleton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    width = lastFrameWidth;
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

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);

    if (state == SKELETON_STATE_CREATE)
    {
        if (animations[ani]->currentFrame == 6)
        {
            SetState(SKELETON_STATE_EXPLODE);
        }
    }
    else if (state == SKELETON_STATE_EXPLODE)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 7000)
        {
            SetState(SKELETON_STATE_DEAD);
        }
    }
    else if (state == SKELETON_STATE_DEAD)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 8000)
        {
            SetState(SKELETON_STATE_CREATE);
            nx = -nx;
        }
    }

}

void Skeleton::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case SKELETON_STATE_CREATE:
        idle_start = GetTickCount();
        animations[SKELETON_ANI_CREATE]->ResetAnimation();
        break;
    case SKELETON_STATE_EXPLODE:
        animations[SKELETON_ANI_EXPLODE]->ResetAnimation();
        break;
    case SKELETON_STATE_DEAD:
        animations[SKELETON_ANI_DEAD]->ResetAnimation();
        break;
    }
}

void Skeleton::Render()
{
    int restart_frame = 0;
    switch (state)
    {
    case SKELETON_STATE_CREATE:
    {
        restart_frame = 0;
        ani = SKELETON_ANI_CREATE; break;
    }
    case SKELETON_STATE_EXPLODE:
    {
        restart_frame = 0;
        ani = SKELETON_ANI_EXPLODE; break;
    }
    case SKELETON_STATE_DEAD:
    {
        ani = SKELETON_ANI_DEAD; break;
    }
    }

    int alpha = 255;
    //animations[ani]->Render(x, y, alpha, restart_frame);
    animations[ani]->Render(x, y, width, lastFrameWidth, lastFrameHeight, alpha, restart_frame, nx);

    RenderBoundingBox();
}