#include "Guard1.h"
void Guard1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    //width = lastFrameWidth;
    height = lastFrameHeight;

    left = x;
    top = y;
    right = left + width;
    bottom = top - height;
}

void Guard1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);
    x += dx;
    y += dy;

    if (state == GUARD1_STATE_IDLE)
    {
        //Chuyển hướng
        if (player_x <= x)
        {
            nx = -1;
            if (player_y <= y && y - player_y <= UNDER_ABOVE_ATTACK_RANGE)   //player dưới khoảng 
            {
                if (x - (player_x + 40) <= GUARD1_ATTACK1_SIZE)   //40 is aladdin idle width and guard1 attack1 size
                {
                    if (start_attack)
                    {
                        if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
                        {
                            SetState(GUARD1_STATE_ATTACK1);
                            start_attack = false;
                        }
                    }
                    else
                    {
                        start_attack = true;
                        attack_start = GetTickCount();
                    }
                }
                else if (x - (player_x + 40) <= GUARD1_TAUNT_SIZE)
                {
                    if (GetTickCount() - idle_start > TAUNT_DELAY_TIME)
                        SetState(GUARD1_STATE_TAUNT);
                }
            }
            else if (player_y - 48 >= y && player_y - 48 - y <= UNDER_ABOVE_ATTACK_RANGE)  //player trên khoảng
            {
                if (x - (player_x + 40) <= GUARD1_ATTACK1_SIZE)   //40 is aladdin idle width, Guard1 ATK 1 size = 40
                {
                    if (start_attack)
                    {
                        if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
                        {
                            SetState(GUARD1_STATE_ATTACK1);
                            start_attack = false;
                        }
                    }
                    else
                    {
                        start_attack = true;
                        attack_start = GetTickCount();
                    }
                }
                else if (x - (player_x + 40) <= GUARD1_TAUNT_SIZE)
                {
                    if (GetTickCount() - idle_start > TAUNT_DELAY_TIME)
                        SetState(GUARD1_STATE_TAUNT);
                }
            }
        }
        else if (player_x >= x)
        {
            nx = 1;
            if (player_y <= y && y - player_y <= UNDER_ABOVE_ATTACK_RANGE)   //player dưới khoảng 
            {
                if (player_x - (x + width) <= GUARD1_ATTACK1_SIZE)
                {
                    if (start_attack)
                    {
                        if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
                        {
                            SetState(GUARD1_STATE_ATTACK1);
                            start_attack = false;
                        }
                    }
                    else
                    {
                        start_attack = true;
                        attack_start = GetTickCount();
                    }
                }
                else if (x - (player_x + 40) <= GUARD1_TAUNT_SIZE)
                {
                    if (GetTickCount() - idle_start > TAUNT_DELAY_TIME)
                    SetState(GUARD1_STATE_TAUNT);
                }
            }
            else if (player_y >= y && player_y - y <= UNDER_ABOVE_ATTACK_RANGE)  //player trên khoảng
            {
                if (player_x - (x + width) <= GUARD1_ATTACK1_SIZE)
                {
                    if (start_attack)
                    {
                        if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
                        {
                            SetState(GUARD1_STATE_ATTACK1);
                            start_attack = false;
                        }
                    }
                    else
                    {
                        start_attack = true;
                        attack_start = GetTickCount();
                    }
                }
                else if (x - (player_x + 40) <= GUARD1_TAUNT_SIZE)
                {
                    if (GetTickCount() - idle_start > TAUNT_DELAY_TIME)
                        SetState(GUARD1_STATE_TAUNT);
                }
            }
        }

    }
    else if (state == GUARD1_STATE_TAUNT)
    {
        if (animations[ani]->currentFrame == 5)
            SetState(GUARD1_STATE_IDLE);

    }
    else if (state == GUARD1_STATE_HURT)
    {
        if (hitpoint <= 0)
            SetState(GUARD1_STATE_DEAD);
        else if (animations[ani]->currentFrame == 5)
            SetState(GUARD1_STATE_IDLE);
    }
    else if (state == GUARD1_STATE_ATTACK1)
    {
        if (animations[ani]->currentFrame == 4)
        {
            SetState(GUARD1_STATE_ATTACK2);
            animations[ani]->currentFrame = -1;
        }
    }
    else if (state == GUARD1_STATE_ATTACK2)
    {
    if (animations[ani]->currentFrame == 4)
        SetState(GUARD1_STATE_IDLE);
    }
    else if (state == GUARD1_STATE_DEAD)
    {
        if (animations[ani]->currentFrame == 9)
            isDead = true;
        return;
    }

    //if (state == GUARD1_STATE_IDLE)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 1000)
    //    {
    //        SetState(GUARD1_STATE_WALK);
    //    }
    //}
    //else if (state == GUARD1_STATE_WALK)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 3000)
    //    {
    //        SetState(GUARD1_STATE_TAUNT);
    //    }
    //}
    //else if (state == GUARD1_STATE_TAUNT)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 5000)
    //    {
    //        SetState(GUARD1_STATE_ATTACK1);
    //    }
    //}
    //else if (state == GUARD1_STATE_ATTACK1)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 7000)
    //    {
    //        SetState(GUARD1_STATE_ATTACK2);
    //    }
    //}
    //else if (state == GUARD1_STATE_ATTACK2)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 9000)
    //    {
    //        SetState(GUARD1_STATE_HURT);
    //    }
    //}
    //else if (state == GUARD1_STATE_HURT)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 11000)
    //    {
    //        SetState(GUARD1_STATE_DEAD);
    //    }
    //}
    //else if (state == GUARD1_STATE_DEAD)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 12000)
    //    {
    //        SetState(GUARD1_STATE_IDLE);
    //        nx = -nx;
    //    }
    //}

}

void Guard1::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case GUARD1_STATE_IDLE:
        idle_start = GetTickCount();
        attack_size = 0;
        break;
    case GUARD1_STATE_WALK:
        animations[GUARD1_ANI_WALK_LEFT]->ResetAnimation();
        animations[GUARD1_ANI_WALK_RIGHT]->ResetAnimation();
        break;
    case GUARD1_STATE_TAUNT:
        Sound::getInstance()->play("GUARD_TAUNT", false, 1);
        idle_start = 0;
        animations[GUARD1_ANI_TAUNT_LEFT]->ResetAnimation();
        animations[GUARD1_ANI_TAUNT_RIGHT]->ResetAnimation();
        break;
    case GUARD1_STATE_ATTACK1:
        Sound::getInstance()->play("ALADDIN_SIT_ATTACK", false, 1);
        idle_start = 0;
        attack_size = GUARD1_ATTACK1_SIZE;
        animations[GUARD1_ANI_ATTACK1_LEFT]->ResetAnimation();
        animations[GUARD1_ANI_ATTACK1_RIGHT]->ResetAnimation();
        break;
    case GUARD1_STATE_ATTACK2:
        Sound::getInstance()->play("ALADDIN_ATTACK", false, 1);
        attack_size = GUARD1_ATTACK2_SIZE;
        animations[GUARD1_ANI_ATTACK2_LEFT]->ResetAnimation();
        animations[GUARD1_ANI_ATTACK2_RIGHT]->ResetAnimation();
        break;
    case GUARD1_STATE_HURT:
        Sound::getInstance()->play("GUARD1_BE_HIT", false, 1);
        attack_size = 0;
        animations[GUARD1_ANI_HURT_LEFT]->ResetAnimation();
        animations[GUARD1_ANI_HURT_RIGHT]->ResetAnimation();
        break;
    case GUARD1_STATE_DEAD:
        Sound::getInstance()->play("ENEMY_DEAD", false, 1);
        //repostion object for explode, explode sprite (90,57)
        if (nx > 0)
            x = x + (BBOX_WIDTH - 90) / 2;
        else
            x = x - (BBOX_WIDTH - 90) / 2;
        y = y + (height - 57) / 2;
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

    //RenderBoundingBox();
}