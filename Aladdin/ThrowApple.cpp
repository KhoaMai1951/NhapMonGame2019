#include "ThrowApple.h"
#include "Guard0.h"
#include "Guard1.h"
#include "Boss.h"

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
    vy -= dt * THROW_APPLE_GRAVITY;
    vx = THROW_APPLE_SPEED*dt*nx;

    if (state == THROW_APPLE_STATE_DESTROYED)
    {
        if (hitBoss)
        {
            if (animations[ani]->currentFrame == 25)
                this->isDead = true;
        }
        else
        {
            if (animations[ani]->currentFrame == 4)
                this->isDead = true;
        }
        return;
    }

    for (UINT i = 0; i < coObjects->size(); i++)
    {
        float t1, l1, r1, b1;
        l1 = coObjects->at(i)->x;
        t1 = coObjects->at(i)->y;
        r1 = coObjects->at(i)->x + coObjects->at(i)->width;
        b1 = coObjects->at(i)->y - coObjects->at(i)->height;
        if (checkOverlap(l1, t1, r1, b1, x, y, x + width, y - height))
        {
            if (dynamic_cast<Enemy *>(coObjects->at(i)) && coObjects->at(i)->isDead != true)
            {
                Enemy* enemy = dynamic_cast<Enemy*>(coObjects->at(i));
                if (enemy->state != 5) // != Dead
                {
                    enemy->hitpoint--;
                    if (dynamic_cast<Guard0*>(enemy) || dynamic_cast<Guard1*>(enemy))
                    {
                        enemy->SetState(4); //4 is hurt
                    }
                }

                if (dynamic_cast<Boss*>(coObjects->at(i)))
                    hitBoss = true;

                SetState(THROW_APPLE_STATE_DESTROYED);
                vx = 0; vy = 0;
            }
            else if (dynamic_cast<Ground *>(coObjects->at(i)))
            {
                SetState(THROW_APPLE_STATE_DESTROYED);
                vx = 0; vy = 0;
            }
        }
    }
    x += vx;
    y += vy;
#pragma region
    //vector<LPCOLLISIONEVENT> coEvents;
    //vector<LPCOLLISIONEVENT> coEventsResult;


    //float l, t, r, b;
    //GetBoundingBox(l, t, r, b);
    //set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->GetGridForCollision(l, t, r, b);
    //vector<CGameObject*> vector_gameobject(set_gameobject.begin(), set_gameobject.end());

    //coEvents.clear();

    //CalcPotentialCollisions(vector_gameobject, coEvents);

    //// No collision occured, proceed normally
    //if (coEvents.size() == 0)
    //{
    //    x += vx;
    //    y += vy;
    //}
    //else
    //{
    //    float min_tx, min_ty, nx = 0, ny;

    //    FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

    //    bool collided = false;
    //    for (UINT i = 0; i < coEventsResult.size(); i++)
    //    {
    //        LPCOLLISIONEVENT e = coEventsResult[i];

    //        if (dynamic_cast<Enemy*>(e->obj))
    //        {
    //            Enemy* enemy = dynamic_cast<Enemy*>(e->obj);
    //            if (enemy->state != 5) // != Dead
    //            {
    //                enemy->hitpoint--;
    //                if (dynamic_cast<Guard0*>(enemy) || dynamic_cast<Guard1*>(enemy))
    //                {
    //                    enemy->SetState(4); //4 is hurt
    //                }
    //            }

    //            SetState(THROW_APPLE_STATE_DESTROYED);
    //            // block 
    //            x += min_tx * dx + nx * 0.1f;
    //            y += min_ty * dy + ny * 0.1f;

    //            if (nx != 0) vx = 0;
    //            if (ny != 0) vy = 0;
    //            collided = true;
    //        }
    //        else if (dynamic_cast<Ground*>(e->obj))
    //        {
    //            SetState(THROW_APPLE_STATE_DESTROYED);
    //            // block 
    //            x += min_tx * dx + nx * 0.1f;
    //            y += min_ty * dy + ny * 0.1f;

    //            if (nx != 0) vx = 0;
    //            if (ny != 0) vy = 0;
    //            collided = true;
    //        }
    //    }
    //    if (!collided)
    //    {
    //        x += vx;
    //        y += vy;
    //    }
    //}

    //// clean up collision events
    //for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion COLLISION (OLD)
}

void ThrowApple::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case THROW_APPLE_STATE_FLYING:
        break;

    case THROW_APPLE_STATE_DESTROYED:
        if (hitBoss)
        {
            Sound::getInstance()->play("GENIE_COLLECT", false, 1);
            if (nx = 1)
                x -= 21;
            y += 26;
            //animations[THROW_APPLE_ANI_BOSS_BE_ATTACKED]->ResetAnimation();
        }
        else
            Sound::getInstance()->play("APPLE_DESTROY", false, 1);
        break;
    }
}

void ThrowApple::Render()
{
    if (state == THROW_APPLE_STATE_FLYING)
    {
        if (nx > 0)
            ani = THROW_APPLE_ANI_FLYING_RIGHT;
        else
            ani = THROW_APPLE_ANI_FLYING_LEFT;
    }
    else if (state == THROW_APPLE_STATE_DESTROYED)
    {
        if (hitBoss)
            ani = THROW_APPLE_ANI_BOSS_BE_ATTACKED;
        else
            ani = THROW_APPLE_ANI_DESTROYED;
    }

    animations[ani]->Render(x, y);
}