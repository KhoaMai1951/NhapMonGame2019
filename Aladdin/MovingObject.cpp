#include "MovingObject.h"

void MovingObject::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
    CGameObject::Update(dt, colliable_objects);
    x += dx;
    y += dy;
}

void MovingObject::Render()
{
    animations[0]->Render(x, y);
}

void MovingObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}
