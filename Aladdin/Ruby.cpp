#include "Ruby.h"

void Ruby::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    right = x + width;
    bottom = y - height;
}

void Ruby::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
    CGameObject::Update(dt, coObjects);

    if (state == RUBY_STATE_EATEN)
        if (animations[ani]->currentFrame == 11)
            this->isDead = true;
}

void Ruby::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case RUBY_STATE_IDLE:
        break;
    case RUBY_STATE_EATEN:
        break;
    }
}

void Ruby::Render()
{
    ani = RUBY_ANI_IDLE;
    if (state == RUBY_STATE_EATEN) {
        ani = RUBY_ANI_EATEN;
    }

    animations[ani]->Render(x, y);

    //RenderBoundingBox();
}