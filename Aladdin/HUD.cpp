#include "HUD.h"

void HUD::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y - height;
}

void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt, coObjects);
}

void HUD::SetState(int state)
{
	/*CGameObject::SetState(state);
	switch (state)
	{

	}*/
}

void HUD::Render()
{
	animations[ani]->Render(x, y);
}