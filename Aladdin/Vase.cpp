#include "Vase.h"

void Vase::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    right = x + width;
    bottom = y - height;
}

void Vase::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
    CGameObject::Update(dt, coObjects);
}

void Vase::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case VASE_STATE_IDLE:
        break;
    case VASE_STATE_EATEN:
        animations[VASE_ANI_EATEN]->ResetAnimation();
        break;
    }
}

void Vase::Render()
{
    int alpha = 255, restart = 0;
    ani = VASE_ANI_IDLE;
    if (state == VASE_STATE_EATEN) {
        ani = VASE_ANI_EATEN;
        restart = 8;
    }

    animations[ani]->Render(x, y, alpha, restart);

    //RenderBoundingBox();
}