#include <algorithm>
#include "debug.h"

#include "Aladdin.h"
#include "Game.h"

//#include "Goomba.h"
#include <set>
#include "SpatialGrid.h"

void Aladdin::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
    // Calculate dx, dy 
    CGameObject::Update(dt);

    // Simple fall down
    vy -= ALADDIN_GRAVITY * dt;

    vector<LPCOLLISIONEVENT> coEvents;
    vector<LPCOLLISIONEVENT> coEventsResult;

    float l, t, r, b;
    GetBoundingBox(l, t, r, b);

    //Lấy các obj thuộc các lưới có chứa player
    RECT temp = ViewPort::getInstance()->InvertY(l, t, r, b, SCREEN_WIDTH, SCREEN_HEIGHT);
    set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(temp.left,
        temp.top, temp.right, temp.bottom);
    //set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(l, t, r, b);

    //Truyền set các obj thuộc các lưới có player vào vector
    vector<CGameObject*> vector_gameobject(set_gameobject.begin(), set_gameobject.end());

    coEvents.clear();

    // turn off collision when die 
    //void CGameObject::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
    if (state != ALADDIN_STATE_DIE)
        CalcPotentialCollisions(vector_gameobject, coEvents);

    // reset untouchable timer if untouchable time has passed
    if (GetTickCount() - untouchable_start > ALADDIN_UNTOUCHABLE_TIME)
    {
        untouchable_start = 0;
        untouchable = 0;
    }

    // No collision occured, proceed normally
    if (coEvents.size() == 0)
    {
        x += dx;
        y += dy;
    }
    else
    {
        float min_tx, min_ty, nx = 0, ny;

        FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

        // Collision logic 
        for (UINT i = 0; i < coEventsResult.size(); i++)
        {
            LPCOLLISIONEVENT e = coEventsResult[i];

            if (dynamic_cast<Apple *>(e->obj)) // if e->obj is Apple 
            {
                Apple *apple = dynamic_cast<Apple *>(e->obj);

                if (e->ny != 0 || e->nx != 0)
                {
                    if (apple->GetState() != APPLE_STATE_DESTROY)
                    {
                        apple->SetState(APPLE_STATE_DESTROY);
                        //apple->isDead = true;
                    }
                }
            }
        }

        // block 
        x += min_tx * dx + nx * 0.4f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
        y += min_ty * dy + ny * 0.4f;

        if (nx != 0) vx = 0;
        if (ny != 0)
        {
            vy = 0;
            if (ny < 0)
                jumping = false;
        }
    }

    // clean up collision events
    for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

    ProcessKeyboard();
}

void Aladdin::ProcessKeyboard()
{
    CGame *game = CGame::GetInstance();
    switch (state)
    {
        int direction;
    case ALADDIN_STATE_DIE: return;
    case ALADDIN_STATE_IDLE:
        direction = game->IsKeyDown(DIK_RIGHT) - game->IsKeyDown(DIK_LEFT);
        if (direction > 0)
        {
            vx = ALADDIN_RUNNING_SPEED;
            nx = 1;
        }
        else if (direction < 0)
        {
            vx = -ALADDIN_RUNNING_SPEED;
            nx = -1;
        }
        else
        {
            SetState(ALADDIN_STATE_IDLE);
        }
        if (game->IsKeyPress(DIK_SPACE))
            SetState(ALADDIN_STATE_JUMP);
        return;
        /*if (game->IsKeyDown(DIK_RIGHT))
        {
            SetState(MARIO_STATE_WALKING_RIGHT); return;
        }
        else if (game->IsKeyDown(DIK_LEFT))
        {
            SetState(MARIO_STATE_WALKING_LEFT); return;
        }
        else
        {
            SetState(MARIO_STATE_IDLE); return;
        }
        if (game->IsKeyDown(DIK_SPACE))
            SetState(MARIO_STATE_JUMP);*/
    //case ALADDIN_STATE_RUNNING_RIGHT:
    //    direction = game->IsKeyDown(DIK_RIGHT) - game->IsKeyDown(DIK_LEFT);
    //    if (direction > 0)
    //    {
    //        SetState(ALADDIN_STATE_RUNNING_RIGHT);
    //    }
    //    else if (direction < 0)
    //    {
    //        SetState(ALADDIN_STATE_RUNNING_LEFT);
    //    }
    //    else
    //    {
    //        SetState(ALADDIN_STATE_IDLE);
    //    }
    //    if (game->IsKeyPress(DIK_SPACE))
    //        SetState(ALADDIN_STATE_JUMP);
    //    return;
    //case ALADDIN_STATE_RUNNING_LEFT:
    //    direction = game->IsKeyDown(DIK_RIGHT) - game->IsKeyDown(DIK_LEFT);
    //    if (direction > 0)
    //    {
    //        SetState(ALADDIN_STATE_RUNNING_RIGHT);
    //    }
    //    else if (direction < 0)
    //    {
    //        SetState(ALADDIN_STATE_RUNNING_LEFT);
    //    }
    //    else
    //    {
    //        SetState(ALADDIN_STATE_IDLE);
    //    }
    //    if (game->IsKeyPress(DIK_SPACE))
    //        SetState(ALADDIN_STATE_JUMP);
    //    return;
    case ALADDIN_STATE_JUMP: 
        if (!jumping)
        {
            state = ALADDIN_STATE_IDLE;
        }
        direction = game->IsKeyDown(DIK_RIGHT) - game->IsKeyDown(DIK_LEFT);
        if (direction > 0)
        {
            vx = ALADDIN_RUNNING_SPEED;
            nx = 1;
        }
        else if (direction < 0)
        {
            vx = -ALADDIN_RUNNING_SPEED;
            nx = -1;
        }
        else
        {
            vx = 0; return;
        }
        return;
    }

}

void Aladdin::SetState(int state)
{
    CGameObject::SetState(state);

    switch (state)
    {
    case ALADDIN_STATE_RUNNING_RIGHT:
        vx = ALADDIN_RUNNING_SPEED;
        nx = 1;
        break;
    case ALADDIN_STATE_RUNNING_LEFT:
        vx = -ALADDIN_RUNNING_SPEED;
        nx = -1;
        break;
    case ALADDIN_STATE_JUMP:
        vy = ALADDIN_JUMP_SPEED_Y;
    case ALADDIN_STATE_IDLE:
        vx = 0;
        break;
    case ALADDIN_STATE_DIE:
        //vy = MARIO_DIE_DEFLECT_SPEED;
        break;
    }
}

void Aladdin::Render()
{
    int ani;
    if (state == ALADDIN_STATE_DIE)
    {
        //ani = MARIO_ANI_DIE;
    }
    else 
       /* if (state == ALADDIN_STATE_IDLE)
        {
            if (nx > 0) ani = ALADDIN_ANI_IDLE_RIGHT;
            else ani = ALADDIN_ANI_IDLE_LEFT;
        }
        else if (state == ALADDIN_STATE_RUNNING_RIGHT)
        {
            ani = ALADDIN_ANI_RUNNING_RIGHT;
        }
        else if (state == ALADDIN_STATE_RUNNING_LEFT)
        {
            ani = ALADDIN_ANI_RUNNING_LEFT;
        }*/
    {
        switch (state)
        {
        case ALADDIN_STATE_IDLE:
        {
            if(vx > 0)
                ani = ALADDIN_ANI_RUNNING_RIGHT; 
            else if (vx < 0)
                ani = ALADDIN_ANI_RUNNING_LEFT; 
            else if (nx > 0) 
                ani = ALADDIN_ANI_IDLE_RIGHT;
            else 
                ani = ALADDIN_ANI_IDLE_LEFT; break;
        }
        case ALADDIN_STATE_JUMP:
        {
            if (nx > 0) ani = ALADDIN_ANI_JUMP_RIGHT;
            else ani = ALADDIN_ANI_JUMP_LEFT;
            break;
        }
        }
    }

    int alpha = 255;
    if (untouchable) alpha = 128;
    animations[ani]->Render(x, y, alpha);

    //RenderBoundingBox();
}

void Aladdin::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;

    if (state == ALADDIN_STATE_IDLE)
    {
        right = x + ALADDIN_IDLE_WIDTH;
        bottom = y - ALADDIN_IDLE_HEIGHT;
    }
    else if (state == ALADDIN_STATE_RUNNING_LEFT || state == ALADDIN_STATE_RUNNING_RIGHT)
    {
        right = x + ALADDIN_IDLE_WIDTH;
        bottom = y - ALADDIN_IDLE_HEIGHT;
    }
}