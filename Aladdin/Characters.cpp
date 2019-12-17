#include "Characters.h"

void Characters::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y - height;
}

void Characters::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt, coObjects);
}

void Characters::SetState(int state)
{
	/*CGameObject::SetState(state);
	switch (state)
	{

	}*/
}

void Characters::Render()
{
	animations[ani]->Render(x, y);
}