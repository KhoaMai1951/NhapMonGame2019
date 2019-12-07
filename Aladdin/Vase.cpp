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

    if (state == VASE_STATE_EATEN)
        if (animations[ani]->currentFrame == 9)
            this->isDead = true;
}

void Vase::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case VASE_STATE_IDLE:
        break;
    case VASE_STATE_EATEN:
        break;
    }
}

void Vase::Render()
{
    ani = VASE_ANI_IDLE;
    if (state == VASE_STATE_EATEN) {
        ani = VASE_ANI_EATEN;
    }

    animations[ani]->Render(x, y);

    //RenderBoundingBox();
}