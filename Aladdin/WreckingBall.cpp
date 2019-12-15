#include "WreckingBall.h"
void WreckingBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
    top = y;
    right = left + width;
    bottom = top - height;
}

void WreckingBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);
    if (name == "ball")
    {
        if (animations[ani]->currentFrame == 12)
        {
            SetState(BALL_STATE_DO_DAMAGE);
        }
        else if (animations[ani]->currentFrame == 17)
        {
            SetState(BALL_STATE_NOT_DO_DAMAGE);
        }
    }
    else if (name == "ball1")
    {
        if (animations[ani]->currentFrame == 2)
        {
            SetState(BALL_STATE_NOT_DO_DAMAGE);
        }
        else if (animations[ani]->currentFrame == 25)
        {
            SetState(BALL_STATE_DO_DAMAGE);
        }
    }

}

void WreckingBall::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case BALL_STATE_DO_DAMAGE:
        do_damage = true;
        break;
    case BALL_STATE_NOT_DO_DAMAGE:
        do_damage = false;
        break;
    }
}

void WreckingBall::Render()
{
    int alpha = 255;
    animations[ani]->Render(x, y);

    //RenderBoundingBox();
}