#include "Apple.h"

void Apple::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    right = x + width;
    bottom = y - height;

    //int lastFrame = animations[ani]->lastFrame;
    ////if (lastFrame < 0) lastFrame = 0;
    ///*   width = animations[ani]->frames[lastFrame]->GetSprite()->width;
    //   height = animations[ani]->frames[lastFrame]->GetSprite()->height;*/
    //width = lastFrameWidth;
    //height = lastFrameHeight;

    ////x += (width - lastFrameWidth) / 2;
    ////y += (height - lastFrameHeight) / 2;

    //left = x;
    //top = y;
    //right = x + width;
    //bottom = y - height;
}

void Apple::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
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
        y -= APPLE_IDLE_WIDTH - APPLE_DESTROY_WIDTH + 1;
        break;
    case APPLE_STATE_IDLE:
        break;
    }
}

void Apple::Render()
{
    ani = APPLE_ANI_IDLE;
    if (state == APPLE_STATE_DESTROY) {
        ani = APPLE_ANI_DESTROY;
    }

    animations[ani]->Render(x, y);
    //animations[ani]->Render(x, y, lastFrameWidth, lastFrameHeight);
    //RenderBoundingBox();
}