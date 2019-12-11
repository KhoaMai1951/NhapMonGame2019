#include "ThrowApple.h"

void ThrowApple::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
    top = y;
    right = left + width;
    bottom = top - height;
}

void ThrowApple::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt);

    // Simple fall down
    //vx += dt*nx*THROW_APPLE_SPEED;
    //vy -= dt*THROW_APPLE_GRAVITY;
    vy -= dt * THROW_APPLE_GRAVITY;
    if (nx == 1)
    {
        vx = dt * THROW_APPLE_SPEED;
    }
    else
        vx = dt * -THROW_APPLE_SPEED;

    if (state == THROW_APPLE_STATE_DESTROYED)
    {
        if (animations[ani]->currentFrame == 4)
            this->isDead = true;
        return;
    }

    vector<LPCOLLISIONEVENT> coEvents;
    vector<LPCOLLISIONEVENT> coEventsResult;


    float l, t, r, b;
    GetBoundingBox(l, t, r, b);
    set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->GetGridForCollision(l, t, r, b);
    vector<CGameObject*> vector_gameobject(set_gameobject.begin(), set_gameobject.end());

    coEvents.clear();

    //void CGameObject::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
    CalcPotentialCollisions(vector_gameobject, coEvents);

    // No collision occured, proceed normally
    if (coEvents.size() == 0)
    {
        x += vx;
        y += vy;
    }
    else
    {
        float min_tx, min_ty, nx = 0, ny;

        FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

        //// block 
        //x += min_tx * dx + nx * 0.1f;
        //y += min_ty * dy + ny * 0.1f;

        //if (nx != 0) vx = 0;
        //if (ny != 0) vy = 0;

        bool collided = false;
        for (UINT i = 0; i < coEventsResult.size(); i++)
        {
            LPCOLLISIONEVENT e = coEventsResult[i];

            if (dynamic_cast<Enemy*>(e->obj) || dynamic_cast<Ground*>(e->obj))
            {
                SetState(THROW_APPLE_STATE_DESTROYED);
                // block 
                x += min_tx * dx + nx * 0.1f;
                y += min_ty * dy + ny * 0.1f;

                if (nx != 0) vx = 0;
                if (ny != 0) vy = 0;
                collided = true;
            }
        }
        if (!collided)
        {
            x += vx;
            y += vy;
        }
    }

    // clean up collision events
    for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void ThrowApple::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case THROW_APPLE_STATE_FLYING:
        break;

    case THROW_APPLE_STATE_DESTROYED:

        break;
    }
}

void ThrowApple::Render()
{
    ani = THROW_APPLE_ANI_FLYING;
    if (state == THROW_APPLE_STATE_DESTROYED) {
        ani = THROW_APPLE_ANI_DESTROYED;
    }

    animations[ani]->Render(x, y);
}