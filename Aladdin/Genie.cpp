#include "Genie.h"

void Genie::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    right = x + width;
    bottom = y - height;
}

void Genie::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
    CGameObject::Update(dt, coObjects);

    if (state == GENIE_STATE_EATEN)
        if (animations[ani]->currentFrame == 4)
            this->isDead = true;
}

void Genie::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case GENIE_STATE_IDLE:
        break;
    case GENIE_STATE_EATEN:
        break;
    }
}

void Genie::Render()
{
    ani = GENIE_ANI_IDLE;
    if (state == GENIE_STATE_EATEN) {
        ani = GENIE_ANI_EATEN;
    }

    animations[ani]->Render(x, y);

    //RenderBoundingBox();
}