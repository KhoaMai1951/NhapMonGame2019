#include <algorithm>
#include "debug.h"

#include "Bar.h"
#include "Game.h"


void CBar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	y += dy;
}

void CBar::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case BAR_MOVE_DOWN:
		vy = BAR_MOVE_SPEED;
		break;
	case BAR_MOVE_UP:
		vy = -BAR_MOVE_SPEED;
		break;
	case BAR_IDLE:
		vy = 0;
		break;
	}
}

void CBar::Move(float _y)
{
    y = _y;
}

void CBar::Render()
{
	//int alpha = 255;
	//if (untouchable) alpha = 128;
	int alpha = 255;
	int ani = 0;
	animations[ani]->Render(x, y, alpha);

	//Vẽ ra BoundingBox
	//RenderBoundingBox();
}

void CBar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = x + BAR_BBOX_WIDTH;
	bottom = y + BAR_BBOX_HEIGHT;
}

