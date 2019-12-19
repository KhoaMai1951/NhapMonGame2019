#include "FlameStrip.h"


void FlameStrip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}

void FlameStrip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt, coObjects);
	if(start_time != 0)
	{
		if (GetTickCount() - start_time > FIRESTRIP_WAITING_TIME)
		{
			start_time = 0;
			do_damage = true;
			ani = FLAMESTRIP_ANI_DO_DAMAGE;
            burn_time = GetTickCount();
		}
	}
    if (do_damage)
        if (GetTickCount() - burn_time > 900)
		{
			SetState(FLAMESTRIP_STATE_NOT_DO_DAMAGE);
            burn_time = 0;
		}
			
	
}

void FlameStrip::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLAMESTRIP_STATE_NOT_DO_DAMAGE:
		do_damage = false;
		break;
	case FLAMESTRIP_STATE_DO_DAMAGE:
		start_time = GetTickCount();
		//animations[ani]->ResetAnimation();
		break;
	}
}

void FlameStrip::Render()
{
	int alpha = 255;
    if (state == FLAMESTRIP_STATE_NOT_DO_DAMAGE)
        ani = FLAMESTRIP_ANI_NOT_DO_DAMAGE;
	animations[ani]->Render(x, y + FLAMESTRIP_HEIGHT);
	RenderBoundingBox();
}