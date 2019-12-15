#include "Bat.h"
void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
    x += dx;
    y += dy;

    if (state == BAT_STATE_IDLE)
    {
        //Chuyển hướng
        //if (player_x <= x)
        //{
        //    nx = -1;
        //    if (player_y <= y && y - player_y <= UNDER_ABOVE_ATTACK_RANGE)   //player dưới khoảng 
        //    {
        //        SetState(BAT_STATE_FLYING);

        //        if (x - (player_x + 40) <= GUARD0_ATTACK_SIZE)
        //        {
        //            if (start_attack)
        //            {
        //                if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
        //                {
        //                    SetState(GUARD0_STATE_ATTACK);
        //                    start_attack = false;
        //                }
        //            }
        //            else
        //            {
        //                start_attack = true;
        //                attack_start = GetTickCount();
        //            }
        //        }
        //    }
        //    else if (player_y - 48 >= y && player_y - 48 - y <= UNDER_ABOVE_ATTACK_RANGE)  //player trên khoảng
        //    {
        //        if (x - (player_x + 40) <= GUARD0_ATTACK_SIZE)   //40 is aladdin idle width
        //        {
        //            if (start_attack)
        //            {
        //                if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
        //                {
        //                    SetState(GUARD0_STATE_ATTACK);
        //                    start_attack = false;
        //                }
        //            }
        //            else
        //            {
        //                start_attack = true;
        //                attack_start = GetTickCount();
        //            }
        //        }
        //    }
        //}
        //else if (player_x >= x)
        //{
        //    nx = 1;
        //    if (player_y <= y && y - player_y <= UNDER_ABOVE_ATTACK_RANGE)   //player dưới khoảng 
        //    {
        //        if (player_x - (x + width) <= GUARD0_ATTACK_SIZE)
        //        {
        //            if (start_attack)
        //            {
        //                if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
        //                {
        //                    SetState(GUARD0_STATE_ATTACK);
        //                    start_attack = false;
        //                }
        //            }
        //            else
        //            {
        //                start_attack = true;
        //                attack_start = GetTickCount();
        //            }
        //        }
        //    }
        //    else if (player_y >= y && player_y - y <= UNDER_ABOVE_ATTACK_RANGE)  //player trên khoảng
        //    {
        //        if (player_x - (x + width) <= GUARD0_ATTACK_SIZE)
        //        {
        //            if (start_attack)
        //            {
        //                if (GetTickCount() - attack_start > GUARD1_ATTACK_DELAY_TIME)
        //                {
        //                    SetState(GUARD0_STATE_ATTACK);
        //                    start_attack = false;
        //                }
        //            }
        //            else
        //            {
        //                start_attack = true;
        //                attack_start = GetTickCount();
        //            }
        //        }
        //    }
        //}
        //40 is aladdin idle width, 48 is aladdin height
        //IF player in bat's attack range
        if ((player_x + 40 >= x - START_ATTACK_RANGE) && (player_x <= x + width + START_ATTACK_RANGE))
        {
            if ((player_y >= y - height - START_ATTACK_RANGE) && (player_y <= y))
            {
                if (GetTickCount() - idle_start > IDLE_TIME)
                    SetState(BAT_STATE_FLYING);
            }
        }
    }
    else if (state == BAT_STATE_FLYING)
    {
        if (GetTickCount() - flying_start > ATTACK_TIME || is_hit == true)
        {
            //Move to idle position
            if (x < idle_x)
                nx = 1;
            else if (x > idle_x)
                nx = -1;
            else nx = 0;

            if (y < idle_y)
                ny = 1;
            else if (y > idle_y)
                ny = -1;
            else ny = 0;

            vx = MOVE_SPEED * dt*nx;
            vy = MOVE_SPEED * dt*ny;

            if((int)x == (int)idle_x && (int)y == (int)idle_y)
                SetState(BAT_STATE_IDLE);
        }
        else
        {
            if (player_x <= x)  //player left
                nx = -1;
            else if (player_x + 40 >= x + width)   //player right
                nx = 1;
            else nx = 0;

            if (player_y - 48 <= y - height)  //player under
                ny = -1;
            else if (player_y >= y)   //player above
                ny = 1;
            else ny = 0;

            vx = MOVE_SPEED * dt*nx;
            vy = MOVE_SPEED * dt*ny;
        }
        
    }
    else if (state == BAT_STATE_DEAD)
    {
        if (animations[ani]->currentFrame == 9)
            isDead = true;
        return;
    }

    if (state != BAT_STATE_DEAD && hitpoint <= 0)
        SetState(BAT_STATE_DEAD);

	/*if (state == BAT_STATE_IDLE)
	{
		if (idle_start != 0 && GetTickCount() - idle_start > 3000)
		{
			SetState(BAT_STATE_FLYING);
		}
	}
	else if (state == BAT_STATE_FLYING)
	{
		if (idle_start != 0 && GetTickCount() - idle_start > 7000)
		{
			SetState(BAT_STATE_DEAD);
		}
	}
	else if (state == BAT_STATE_DEAD)
	{
		if (idle_start != 0 && GetTickCount() - idle_start > 8000)
		{
			SetState(BAT_STATE_IDLE);
		}
	}*/

}

void Bat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_STATE_IDLE:
        nx = 1;
        vx = 0; vy = 0;
        is_hit = false;
        flying_start = 0;
		idle_start = GetTickCount();
		break;
	case BAT_STATE_FLYING:
        flying_start = GetTickCount();
        idle_start = 0;
		animations[BAT_ANI_FLYING]->ResetAnimation();
		break;
    case BAT_STATE_DEAD:
        nx = 1;
        vx = 0, vy = 0;
        //repostion object for explode, bat sprite(34,25), explode sprite (90,57)
        x = x + (34 - 90) / 2;
        y = y + (25 - 57) / 2;
		animations[BAT_ANI_DEAD]->ResetAnimation();
		break;
	}
}

void Bat::Render()
{
	int restart_frame = 0;
	switch (state)
	{
	case BAT_STATE_IDLE:
	{
		restart_frame = 0;
		ani = BAT_ANI_IDLE; break;
	}
	case BAT_STATE_FLYING:
	{
		restart_frame = 3;
		ani = BAT_ANI_FLYING; break;
	}
	case BAT_STATE_DEAD:
	{
		ani = BAT_ANI_DEAD; break;
	}
	}

	int alpha = 255;
	//animations[ani]->Render(x, y, alpha, restart_frame);
	animations[ani]->Render(x, y, width, lastFrameWidth, lastFrameHeight, alpha, restart_frame, nx);

	//RenderBoundingBox();
}