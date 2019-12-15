#include "Guard0.h"
void Guard0::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//width = lastFrameWidth;
	height = lastFrameHeight;

	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}

void Guard0::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

    if (state == GUARD0_STATE_IDLE)
    {
        //Chuyển hướng
        if (player_x <= x)
        {
            nx = -1;
            if (player_y <= y && y - player_y <= UNDER_ABOVE_ATTACK_RANGE)   //player dưới khoảng 
            {
                if (x - (player_x + 40) <= GUARD0_ATTACK_SIZE)
                {
                    if (start_attack)
                    {
                        if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
                        {
                            SetState(GUARD0_STATE_ATTACK);
                            start_attack = false;
                        }
                    }
                    else
                    {
                        start_attack = true;
                        attack_start = GetTickCount();
                    } 
                }
            }
            else if (player_y - 48 >= y && player_y - 48 - y <= UNDER_ABOVE_ATTACK_RANGE)  //player trên khoảng
            {
                if (x - (player_x + 40) <= GUARD0_ATTACK_SIZE)   //40 is aladdin idle width
                {
                    if (start_attack)
                    {
                        if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
                        {
                            SetState(GUARD0_STATE_ATTACK);
                            start_attack = false;
                        }
                    }
                    else
                    {
                        start_attack = true;
                        attack_start = GetTickCount();
                    }
                }
            }
        } 
        else if (player_x >= x)
        {
            nx = 1;
            if (player_y <= y && y - player_y <= UNDER_ABOVE_ATTACK_RANGE)   //player dưới khoảng 
            {
                if (player_x - (x + width) <= GUARD0_ATTACK_SIZE)
                {
                    if (start_attack)
                    {
                        if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
                        {
                            SetState(GUARD0_STATE_ATTACK);
                            start_attack = false;
                        }
                    }
                    else
                    {
                        start_attack = true;
                        attack_start = GetTickCount();
                    }
                }
            }
            else if (player_y >= y && player_y - y <= UNDER_ABOVE_ATTACK_RANGE)  //player trên khoảng
            {
                if (player_x - (x + width) <= GUARD0_ATTACK_SIZE)
                {
                    if (start_attack)
                    {
                        if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
                        {
                            SetState(GUARD0_STATE_ATTACK);
                            start_attack = false;
                        }
                    }
                    else
                    {
                        start_attack = true;
                        attack_start = GetTickCount();
                    }
                }
            }
        }  

    }
    else if (state == GUARD0_STATE_HURT)
    {
        if (hitpoint <= 0)
            SetState(GUARD0_STATE_DEAD);
        else if (animations[ani]->currentFrame == 8)
            SetState(GUARD0_STATE_IDLE);
    }
    else if (state == GUARD0_STATE_ATTACK)
    {
        if (animations[ani]->currentFrame == 5)
            SetState(GUARD0_STATE_IDLE);
    }
    else if (state == GUARD0_STATE_DEAD)
    {
        if (animations[ani]->currentFrame == 9)
            isDead = true;
        return;
    }
        
    //if (state == GUARD0_STATE_IDLE)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 1000)
    //    {
    //        SetState(GUARD0_STATE_WALK);
    //    }
    //}
    //else if (state == GUARD0_STATE_WALK)
    //{
    //    if(idle_start != 0 && GetTickCount() - idle_start > 3000)
    //    {
    //        SetState(GUARD0_STATE_ATTACK);
    //    }
    //}
    //else if (state == GUARD0_STATE_ATTACK)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 5000)
    //    {
    //        SetState(GUARD0_STATE_HURT);
    //    }
    //}
    //else if (state == GUARD0_STATE_HURT)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 7000)
    //    {
    //        SetState(GUARD0_STATE_DEAD);
    //    }
    //}
    //else if (state == GUARD0_STATE_DEAD)
    //{
    //    if (idle_start != 0 && GetTickCount() - idle_start > 8000)
    //    {
    //        SetState(GUARD0_STATE_IDLE);
    //        nx = -nx;
    //    }
    //}

}

void Guard0::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GUARD0_STATE_IDLE:
            attack_size = 0;
            idle_start = GetTickCount();
			break;
		case GUARD0_STATE_WALK:
			animations[GUARD0_ANI_WALK_LEFT]->ResetAnimation();
			animations[GUARD0_ANI_WALK_RIGHT]->ResetAnimation();
			break;
		case GUARD0_STATE_ATTACK:
            attack_size = GUARD0_ATTACK_SIZE;
			animations[GUARD0_ANI_ATTACK_LEFT]->ResetAnimation();
			animations[GUARD0_ANI_ATTACK_RIGHT]->ResetAnimation();
			break;
		case GUARD0_STATE_HURT:
            attack_size = 0;
			animations[GUARD0_ANI_HURT_LEFT]->ResetAnimation();
			animations[GUARD0_ANI_HURT_RIGHT]->ResetAnimation();
			break;
		case GUARD0_STATE_DEAD:
            //repostion object for explode, explode sprite (90,57)
            if(nx > 0)
                x = x + (BBOX_WIDTH - 90) / 2;
            else
                x = x - (BBOX_WIDTH - 90) / 2;
            y = y + (height - 57) / 2;
			animations[GUARD0_ANI_DEAD]->ResetAnimation();
			break;
	}
}

void Guard0::Render()
{
	int restart_frame = 0;
	switch (state)
	{
        case GUARD0_STATE::GUARD0_STATE_IDLE:
        {
	        restart_frame = 0;
	        if (nx > 0)
		        ani = GUARD0_ANI_IDLE_RIGHT;
	        else
		        ani = GUARD0_ANI_IDLE_LEFT;
            break;
        }
        case GUARD0_STATE::GUARD0_STATE_WALK:
        {
	        restart_frame = 0;
	        if (nx > 0)
		        ani = GUARD0_ANI_WALK_RIGHT;
	        else if (vx < 0)
		        ani = GUARD0_ANI_WALK_LEFT;
	        break;
        }
        case GUARD0_STATE::GUARD0_STATE_ATTACK:
        {
	        restart_frame = 0;
	        if (nx > 0)
		        ani = GUARD0_ANI_ATTACK_RIGHT;
	        else if (nx < 0)
		        ani = GUARD0_ANI_ATTACK_LEFT;
	        break;
        }
        case GUARD0_STATE::GUARD0_STATE_HURT:
        {
	        restart_frame = 0;
	        if (nx > 0)
		        ani = GUARD0_ANI_HURT_RIGHT;
	        else if (nx < 0)
		        ani = GUARD0_ANI_HURT_LEFT;
	        break;
        }
        case GUARD0_STATE::GUARD0_STATE_DEAD:
        {
            restart_frame = 0;
            ani = GUARD0_ANI_DEAD;
            break;
        }
        default:
            restart_frame = 0;
            if (nx > 0)
                ani = GUARD0_ANI_IDLE_RIGHT;
            else
                ani = GUARD0_ANI_IDLE_LEFT;
	}

	int alpha = 255;
	//animations[ani]->Render(x, y, alpha, restart_frame);
	animations[ani]->Render(x, y, width, lastFrameWidth, lastFrameHeight, alpha, restart_frame, nx);

	//RenderBoundingBox();
}