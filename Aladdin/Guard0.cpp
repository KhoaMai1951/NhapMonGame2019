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

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	/*x += dx;
	y += dy;*/

}

void Guard0::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case STATE_IDLE:
			//idle_start = 0;
			break;
		case STATE_WALK:
			animations[ANI_WALK_LEFT]->ResetAnimation();
			animations[ANI_WALK_RIGHT]->ResetAnimation();
			break;
		case STATE_ATTACK:
			animations[ANI_ATTACK_LEFT]->ResetAnimation();
			animations[ANI_ATTACK_RIGHT]->ResetAnimation();
			break;
		case STATE_HURT:
			animations[ANI_HURT_LEFT]->ResetAnimation();
			animations[ANI_HURT_RIGHT]->ResetAnimation();
			break;
		case STATE_DEAD:
			animations[ANI_DEAD]->ResetAnimation();
			break;
	}
}

void Guard0::Render()
{
	int restart_frame = 0;
	if (state == STATE_DEAD)
	{
		restart_frame = 0;
		ani = ANI_DEAD;
	}
	else
	{
		switch (state)
		{
		case GUARD0_STATE::STATE_IDLE:
		{
			restart_frame = 0;
			if (nx > 0)
				ani = ANI_IDLE_RIGHT;
			else
				ani = ANI_IDLE_LEFT; break;
		}
		case GUARD0_STATE::STATE_WALK:
		{
			restart_frame = 0;
			if (vx > 0)
				ani = ANI_WALK_RIGHT;
			else if (vx < 0)
				ani = ANI_WALK_LEFT;
			break;
		}
		case GUARD0_STATE::STATE_ATTACK:
		{
			restart_frame = 0;
			if (nx > 0)
				ani = ANI_ATTACK_RIGHT;
			else if (nx < 0)
				ani = ANI_ATTACK_LEFT;
			break;
		}
		case GUARD0_STATE::STATE_HURT:
		{
			restart_frame = 0;
			if (nx > 0)
				ani = ANI_HURT_RIGHT;
			else if (nx < 0)
				ani = ANI_HURT_LEFT;
			break;
		}
		}
	}

	int alpha = 255;
	//animations[ani]->Render(x, y, alpha, restart_frame);
	animations[ani]->Render(x, y, width, lastFrameHeight, alpha, restart_frame, nx);

	RenderBoundingBox();
}