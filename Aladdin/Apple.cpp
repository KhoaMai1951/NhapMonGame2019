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
    CGameObject::Update(dt, coObjects);

   /* vector<LPCOLLISIONEVENT> coEvents;
    vector<LPCOLLISIONEVENT> coEventsResult;

    float l, t, r, b;
    GetBoundingBox(l, t, r, b);

    RECT temp = ViewPort::getInstance()->InvertY(l, t, r, b, SCREEN_WIDTH, SCREEN_HEIGHT);
    set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(temp.left,
        temp.top, temp.right, temp.bottom);
    vector<CGameObject*> vector_gameobject(set_gameobject.begin(), set_gameobject.end());

    coEvents.clear();

    CalcPotentialCollisions(vector_gameobject, coEvents);*/

    //// No collision occured, proceed normally
    //if (coEvents.size() == 0)
    //{
    //    x += dx;
    //    y += dy;
    //}
    //else
    //{
    //    float min_tx = 1.0f;
    //    float min_ty = 1.0f;
    //    float nx = 0.0f;
    //    float ny = 0.0f;

    //    FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

        //// Collision logic with player
        //for (UINT i = 0; i < coEventsResult.size(); i++)
        //{
        //    LPCOLLISIONEVENT e = coEventsResult[i];

        //    if (dynamic_cast<Aladdin *>(e->obj)) // if e->obj is aladdin
        //    {
        //        Aladdin *aladdin = dynamic_cast<Aladdin *>(e->obj);

        //        // jump on top >> kill Goomba and deflect a bit 
        //        goomba->SetState(GOOMBA_STATE_DIE);
        //        vy = MARIO_JUMP_DEFLECT_SPEED;
        //        else if (e->nx != 0)
        //        {
        //            if (untouchable == 0)
        //            {
        //                if (goomba->GetState() != GOOMBA_STATE_DIE)
        //                {
        //                    if (level > MARIO_LEVEL_SMALL)
        //                    {
        //                        level = MARIO_LEVEL_SMALL;
        //                        StartUntouchable();
        //                    }
        //                    else
        //                        SetState(MARIO_STATE_DIE);
        //                }
        //            }
        //        }
        //    }
        //}

    //    x += min_tx * dx + nx * 0.4f;
    //    y += min_ty * dy + ny * 0.4f;

    //    if (nx != 0 && ny == 0)
    //    {
    //        vx = 0;
    //        facing = -facing;
    //    }
    //    if (ny != 0)
    //        vy = 0;
    //}

    //for (UINT i = 0; i < coEvents.size(); i++)
    //    delete coEvents[i];

    //vx = facing * 0.04f;
    //
    // TO-DO: make sure Goomba can interact with the world and to each of them too!
    // 
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
    int ani = APPLE_ANI_IDLE;
    if (state == APPLE_STATE_DESTROY) {
        ani = APPLE_ANI_DESTROY;
    }

    animations[ani]->Render(x, y);
    //RenderBoundingBox();
}