#include <algorithm>
#include "debug.h"

#include "Aladdin.h"

//#include "Goomba.h"

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

    //switch (state)
    //{
    //case ALADDIN_STATE_JUMP:
    //{
    //    if(ani == ALADDIN_ANI_JUMP_RIGHT || ani == ALADDIN_ANI_JUMP_LEFT)
    //         if(animations[ani]->currentFrame == 3) //frame bắt đầu nhảy
    //            vy = ALADDIN_JUMP_SPEED_Y;
    //    break;
    //}
    //}

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
        //coEventsResult = GetWallCollision(coEvents, min_tx, min_ty, nx, ny);

        // Collision logic 

        // block 
        x += min_tx * dx + nx * 0.1f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
        y += min_ty * dy + ny * 0.1f;

        if (nx != 0) vx = 0;
        if (ny != 0)
        {
            vy = 0;
            if (ny > 0)
                jumping = false;
        }
    }

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
                }
            }
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
        int direction, updown;
    case ALADDIN_STATE_DIE: return;
    case ALADDIN_STATE_IDLE: 
    case ALADDIN_STATE_CROUCH: 
    case ALADDIN_STATE_LOOKUP:
    {
        updown = game->IsKeyDown(DIK_UP) - game->IsKeyDown(DIK_DOWN);
        direction = game->IsKeyDown(DIK_RIGHT) - game->IsKeyDown(DIK_LEFT);
        if (updown > 0)
        {
            if (direction > 0)
                nx = 1;
            else
                nx = -1;
            if(state != ALADDIN_STATE_LOOKUP)
                SetState(ALADDIN_STATE_LOOKUP);
        }
        else if (updown < 0)
        {
            if (direction > 0)
                nx = 1;
            else
                nx = -1;
            if (state != ALADDIN_STATE_CROUCH)
                SetState(ALADDIN_STATE_CROUCH);
        }
        else
        {
            SetState(ALADDIN_STATE_IDLE);
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
        }
        if (game->IsKeyPress(DIK_SPACE))
        {
            if (vx == 0)
                SetState(ALADDIN_STATE_JUMP);
            else
                SetState(ALADDIN_STATE_RUN_JUMP);
        }
        return;
    }
    case ALADDIN_STATE_JUMP: 
    case ALADDIN_STATE_RUN_JUMP:
    {
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
            vx = 0;
        }
        return;
    }
    }

}

void Aladdin::SetState(int state)
{
    CGameObject::SetState(state);

    switch (state)
    {
    case ALADDIN_STATE_JUMP:
    {
        jumping = true;
        vy = ALADDIN_JUMP_SPEED_Y;

        animations[ALADDIN_ANI_JUMP_RIGHT]->ResetAnimation();
        animations[ALADDIN_ANI_JUMP_LEFT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_RUN_JUMP:
    {
        jumping = true;
        vy = ALADDIN_JUMP_SPEED_Y;
        
        animations[ALADDIN_ANI_RUN_JUMP_RIGHT]->ResetAnimation();
        animations[ALADDIN_ANI_RUN_JUMP_LEFT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_IDLE:
        vx = 0;
        break;
    case ALADDIN_STATE_CROUCH:
    {
        vx = 0;
        animations[ALADDIN_ANI_CROUCH_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_CROUCH_RIGHT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_LOOKUP:
    {
        vx = 0;
        animations[ALADDIN_ANI_LOOKUP_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_LOOKUP_RIGHT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_DIE:
        //vy = MARIO_DIE_DEFLECT_SPEED;
        break;
    }
}

void Aladdin::Render()
{
    int restart_frame = 0; //for jump
    if (state == ALADDIN_STATE_DIE)
    {
        restart_frame = 0;
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
            restart_frame = 0;
            if(vx > 0)
                ani = ALADDIN_ANI_RUNNING_RIGHT; 
            else if (vx < 0)
                ani = ALADDIN_ANI_RUNNING_LEFT; 
            else if (nx > 0) 
                ani = ALADDIN_ANI_IDLE_RIGHT;
            else 
                ani = ALADDIN_ANI_IDLE_LEFT;break;
        }
        case ALADDIN_STATE_JUMP:
        {
            restart_frame = 5;
            if (nx > 0) ani = ALADDIN_ANI_JUMP_RIGHT;
            else ani = ALADDIN_ANI_JUMP_LEFT;
            break;
        }
        case ALADDIN_STATE_RUN_JUMP:
        {
            restart_frame = 5;
            if (nx > 0) ani = ALADDIN_ANI_RUN_JUMP_RIGHT;
            else ani = ALADDIN_ANI_RUN_JUMP_LEFT;
            break;
        }
        case ALADDIN_STATE_LOOKUP:
        {
            restart_frame = 2;
            if (nx > 0)
                ani = ALADDIN_ANI_LOOKUP_RIGHT;
            else
                ani = ALADDIN_ANI_LOOKUP_LEFT;
            break;
        }
        case ALADDIN_STATE_CROUCH:
        {
            restart_frame = 3;
            if (nx > 0)
                ani = ALADDIN_ANI_CROUCH_RIGHT;
            else
                ani = ALADDIN_ANI_CROUCH_LEFT;
            break;
        }
        }
    }

    int alpha = 255;
    if (untouchable) alpha = 128;
    animations[ani]->Render(x, y, alpha, restart_frame);

    //RenderBoundingBox();
}

void Aladdin::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    left = x;
    top = y;
    /*if (state == ALADDIN_STATE_IDLE)
    {
        right = x + ALADDIN_IDLE_WIDTH;
        bottom = y - ALADDIN_IDLE_HEIGHT;
    }
    else if (state == ALADDIN_STATE_JUMP || state == ALADDIN_STATE_RUN_JUMP || s)
    {
        right = x + ALADDIN_IDLE_WIDTH;
        bottom = y - ALADDIN_IDLE_HEIGHT;
    }*/
    switch (state)
    {
    case ALADDIN_STATE_IDLE:
        right = x + ALADDIN_IDLE_WIDTH;
        bottom = y - ALADDIN_IDLE_HEIGHT;
        break;
    default:
        right = x + ALADDIN_IDLE_WIDTH;
        bottom = y - ALADDIN_IDLE_HEIGHT;
    }
}

//vector<CCollisionEvent*> Aladdin::GetWallCollision(vector<CCollisionEvent*> &coEvents, float &min_tx, float &min_ty, float &nx, float &ny)
//{
//    int min_ix = -1;
//    int min_iy = -1;
//    min_tx = 1.0f;
//    min_ty = 1.0f;
//    nx = 0.0f;
//    ny = 0.0f;
//
//    vector<CCollisionEvent*> result;
//    for (int i = coEvents.size() - 1; i >= 0; --i)
//    {
//        CCollisionEvent* c = coEvents[i];
//        if (dynamic_cast<Ground*>(c->obj))
//        {
//            if (c->t < min_tx && c->nx != 0)
//            {
//                min_tx = c->t;
//                nx = c->nx;
//                min_ix = i;
//            }
//            if (c->t < min_ty  && c->ny != 0)
//            {
//                min_ty = c->t;
//                ny = c->ny;
//                min_iy = i;
//            }
//        }
//    }
//    if (min_ix >= 0)
//        result.push_back(coEvents[min_ix]);
//    if (min_iy >= 0)
//        result.push_back(coEvents[min_iy]);
//    return result;
//};


//vector<CCollisionEvent*> Aladdin::GetEnemyCollision(vector<CCollisionEvent*> &coEvents)
//{
//    vector<CCollisionEvent*> result;
//    for (int i = coEvents.size() - 1; i >= 0; --i)
//        if (dynamic_cast<Enemy*>(coEvents[i]->obj) || dynamic_cast<Enemy_Bullet*>(coEvents[i]->obj))
//            if ((coEvents[i]->ny != 0 || coEvents[i]->nx != 0) && untouchable < 0)
//            {
//                SetState(NINJA_HURT);
//                result.push_back(coEvents[i]);
//            }
//    return result;
//};