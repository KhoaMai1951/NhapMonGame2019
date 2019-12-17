#include "Apple.h"

void Apple::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    right = x + width;
    bottom = y - height;
}

void Apple::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
    if (isDead) return;
    CGameObject::Update(dt, coObjects);

    if (state == APPLE_STATE_DESTROY)
        if (animations[ani]->currentFrame == 11)
            this->isDead = true;
	
}

void Apple::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case APPLE_STATE_DESTROY:
        Sound::getInstance()->play("APPLE_COLLECT", false, 1);
        y -= APPLE_IDLE_WIDTH - APPLE_DESTROY_WIDTH + 1;
        break;
    case APPLE_STATE_IDLE:
        break;
    }
}

void Apple::Render()
{
    if (isDead) return;
    ani = APPLE_ANI_IDLE;
    if (state == APPLE_STATE_DESTROY) {
        ani = APPLE_ANI_DESTROY;
    }

    animations[ani]->Render(x, y);
    //animations[ani]->Render(x, y, lastFrameWidth, lastFrameHeight);
    //RenderBoundingBox();
}