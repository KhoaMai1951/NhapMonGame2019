#include "Health.h"

void Health::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y - height;
}

void Health::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void Health::SetState(int state)
{
	CGameObject::SetState(state);
}

void Health::Render()
{
	ani = 8;
	/*switch (state)
	{
	case HEALTH_STATE_0:
		ani = HEALTH_ANI_0;
		break;
	case HEALTH_STATE_1:
		ani = HEALTH_ANI_1;
		break;
	case HEALTH_STATE_2:
		ani = HEALTH_ANI_2;
		break;
	case HEALTH_STATE_3:
		ani = HEALTH_ANI_3;
		break;
	case HEALTH_STATE_4:
		ani = HEALTH_ANI_4;
		break;
	case HEALTH_STATE_5:
		ani = HEALTH_ANI_6;
		break;
	case HEALTH_STATE_6:
		ani = HEALTH_ANI_6;
	case HEALTH_STATE_7:
		ani = HEALTH_ANI_7;
		break;
	case HEALTH_STATE_8:
		ani = HEALTH_ANI_8;
		break;
	}*/


	ani = (8 * HealthRatio);

	animations[ani]->Render(x, y);

	//RenderBoundingBox();
}