#include "Chains.h"
void Chains::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
    top = y;
    right = left + width;
    bottom = top - height;
}

void Chains::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);
}

void Chains::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case CHAINS_STATE_IDLE:
        break;
    }
}

void Chains::Render()
{
    int alpha = 255;
    animations[ani]->Render(x, y);

    //RenderBoundingBox();
}