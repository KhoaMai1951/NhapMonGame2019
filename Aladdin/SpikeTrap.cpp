#include "SpikeTrap.h"
void SpikeTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
    top = y;
    right = left + width;
    bottom = top - height;
}

void SpikeTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);
    
    if (name == "spike")
    {
        if (animations[ani]->currentFrame == 4)
        {
            SetState(STATE_DO_DAMAGE);
        }
        else if (animations[ani]->currentFrame == 5)
        {
            SetState(STATE_NOT_DO_DAMAGE);
        }
    }
    else if (name == "spike1")
    {
        if (animations[ani]->currentFrame == 9)
        {
            SetState(STATE_NOT_DO_DAMAGE);
        }
        else if (animations[ani]->currentFrame == 1)
        {
            SetState(STATE_DO_DAMAGE);
        }
    }

}

void SpikeTrap::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case STATE_DO_DAMAGE:
        //Sound::getInstance()->play("SPIKE_OUT", false, 1);
        do_damage = true;
        break;
    case STATE_NOT_DO_DAMAGE:
        do_damage = false;
        break;
    }
}

void SpikeTrap::Render()
{
    int alpha = 255;
    animations[ani]->Render(x, y);

    //RenderBoundingBox();
}