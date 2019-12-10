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

	if (state == BAT_STATE_IDLE)
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
	}

}

void Bat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_STATE_IDLE:
		idle_start = GetTickCount();
		break;
	case BAT_STATE_FLYING:
		animations[BAT_ANI_FLYING]->ResetAnimation();
		break;
	case BAT_STATE_DEAD:
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