#include "Step.h"
void Step::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
    top = y;
    right = left + width;
    bottom = top - height;
}

void Step::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);
    if (animations[ani]->currentFrame ==3)
    {
        SetState(STATE_STANDABLE);
    }
    else if(animations[ani]->currentFrame == 6)
    {
        SetState(STATE_NOT_STANDABLE);
    }

}

void Step::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case STATE_STANDABLE:
        standable = true;
        break;
    case STATE_NOT_STANDABLE:
        standable = false;
        break;
    }
}

void Step::Render()
{
    int alpha = 255;
    animations[ani]->Render(x, y);

    //RenderBoundingBox();
}