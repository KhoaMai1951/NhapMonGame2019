#include "LifeHeal.h"

void LifeHeal::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    right = x + width;
    bottom = y - height;
}

void LifeHeal::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
    CGameObject::Update(dt, coObjects);

    if (state == LIFEHEAL_STATE_EATEN)
        if (animations[ani]->currentFrame == 11)
            this->isDead = true;
}

void LifeHeal::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case LIFEHEAL_STATE_IDLE:
        break;
    case LIFEHEAL_STATE_EATEN:
        Sound::getInstance()->play("LIFEHEAL_COLLECT", false, 1);
        break;
    }
}

void LifeHeal::Render()
{
    ani = LIFEHEAL_ANI_IDLE;
    if (state == LIFEHEAL_STATE_EATEN) {
        ani = LIFEHEAL_ANI_EATEN;
    }

    animations[ani]->Render(x, y);

    //RenderBoundingBox();
}