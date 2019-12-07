#include "Guard0.h"
void Guard0::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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

void Guard0::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

    if (state == GUARD0_STATE_IDLE)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 1000)
        {
            SetState(GUARD0_STATE_WALK);
        }
    }
    else if (state == GUARD0_STATE_WALK)
    {
        if(idle_start != 0 && GetTickCount() - idle_start > 3000)
        {
            SetState(GUARD0_STATE_ATTACK);
        }
    }
    else if (state == GUARD0_STATE_ATTACK)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 5000)
        {
            SetState(GUARD0_STATE_HURT);
        }
    }
    else if (state == GUARD0_STATE_HURT)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 7000)
        {
            SetState(GUARD0_STATE_DEAD);
        }
    }
    else if (state == GUARD0_STATE_DEAD)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 8000)
        {
            SetState(GUARD0_STATE_IDLE);
            nx = -nx;
        }
    }

}

void Guard0::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GUARD0_STATE_IDLE:
            idle_start = GetTickCount();
			break;
		case GUARD0_STATE_WALK:
			animations[GUARD0_ANI_WALK_LEFT]->ResetAnimation();
			animations[GUARD0_ANI_WALK_RIGHT]->ResetAnimation();
			break;
		case GUARD0_STATE_ATTACK:
			animations[GUARD0_ANI_ATTACK_LEFT]->ResetAnimation();
			animations[GUARD0_ANI_ATTACK_RIGHT]->ResetAnimation();
			break;
		case GUARD0_STATE_HURT:
			animations[GUARD0_ANI_HURT_LEFT]->ResetAnimation();
			animations[GUARD0_ANI_HURT_RIGHT]->ResetAnimation();
			break;
		case GUARD0_STATE_DEAD:
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
	animations[ani]->Render(x, y, width, lastFrameHeight, alpha, restart_frame, nx);

	RenderBoundingBox();
}