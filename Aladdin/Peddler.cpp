#include "Peddler.h"
void Peddler::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    //width = lastFrameWidth;
    height = lastFrameHeight;

    left = x;
    top = y;
    right = left + width;
    bottom = top - height;
}

void Peddler::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    //CGameObject::Update(dt, coObjects);
    //x += dx;
    //y += dy;

    if (state == PEDDLER_STATE_IDLE)
    {
        if (idle_start > 0)
        {
            if (GetTickCount() - idle_start > IDLE_TIME)
                SetState(PEDDLER_STATE_OPEN_SHOP);
        }
        else if ((player_x + 40 >= x - START_OPEN_SHOP_RANGE) && (player_x <= x + width + START_OPEN_SHOP_RANGE))
        {
            if ((player_y >= y - height - START_OPEN_SHOP_RANGE) && (player_y <= y + 100))
            {
                idle_start = GetTickCount();
            }
        }
    }
    else if (!shop_opened && animations[ani]->currentFrame == 35)
    {
        shop_opened = true;
    }

}

void Peddler::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case PEDDLER_STATE_IDLE:
        break;
    case PEDDLER_STATE_OPEN_SHOP:
        Sound::getInstance()->play("PEDDLER", false, 1);
        break;
    }
}

void Peddler::Render()
{
    int restart_frame = 0;
    switch (state)
    {
    case PEDDLER_STATE_IDLE:
    {
        restart_frame = 1;
        ani = PEDDLER_ANI_IDLE; break;
    }
    case PEDDLER_STATE_OPEN_SHOP:
    {
        restart_frame = 35;
        ani = PEDDLER_ANI_OPEN_SHOP; break;
    }
    }

    int alpha = 255;
    //animations[ani]->Render(x, y, alpha, restart_frame);
    animations[ani]->Render(x, y, width, lastFrameWidth, lastFrameHeight, alpha, restart_frame, nx);

    //RenderBoundingBox();
}