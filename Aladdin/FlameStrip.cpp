#include "FlameStrip.h"


void FlameStrip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	height = lastFrameHeight;

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
		}
	}
	if (do_damage)
		if (animations[ani]->currentFrame == 8)
		{
			animations[ani]->ResetAnimation();
			SetState(FLAMESTRIP_STATE_NOT_DO_DAMAGE);
		}
			
	
}

void FlameStrip::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLAMESTRIP_STATE_NOT_DO_DAMAGE:
		do_damage = false;
		ani = FLAMESTRIP_ANI_NOT_DO_DAMAGE;
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
	//animations[ani]->Render(x, y);
	animations[ani]->Render(x, y, width, lastFrameHeight, alpha, 0, nx);
	//RenderBoundingBox();
}