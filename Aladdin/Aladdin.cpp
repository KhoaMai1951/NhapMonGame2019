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

    if (state == ALADDIN_STATE_IDLE)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 5000)
        {
            SetState(ALADDIN_STATE_IDLE1);
        }
    }
    if (state == ALADDIN_STATE_ATTACK)
    {
        if (animations[ani]->currentFrame == 4)
            SetState(ALADDIN_STATE_IDLE);
    }
    else if (state == ALADDIN_STATE_IDLE1)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 7000)
        {
            SetState(ALADDIN_STATE_IDLE2);
        }
    }
    else if (state == ALADDIN_STATE_IDLE2)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 15000)
        {
            SetState(ALADDIN_STATE_IDLE3);
        }
    }
    else if (state == ALADDIN_STATE_IDLE3 && animations[ani]->currentFrame == 17)
    {
        SetState(ALADDIN_STATE_IDLE);
    }

#pragma region Find objects in grid
    float l, t, r, b;
    GetBoundingBox(l, t, r, b);

    //Lấy các obj thuộc các lưới có chứa player
    RECT temp = ViewPort::getInstance()->InvertY(l, t, r, b, SCREEN_WIDTH, SCREEN_HEIGHT);
    set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->GetGridForCollision(temp.left,
        temp.top, temp.right, temp.bottom);
    //set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(l, t, r, b);

    //Truyền set các obj thuộc các lưới có player vào vector
    vector<CGameObject*> vector_gameobject(set_gameobject.begin(), set_gameobject.end());
#pragma endregion 

    // turn off collision when die 
    if (state == ALADDIN_STATE_DEAD)
        return;
    //// reset untouchable timer if untouchable time has passed
    //if (GetTickCount() - untouchable_start > ALADDIN_UNTOUCHABLE_TIME)
    //{
    //    untouchable_start = 0;
    //    untouchable = 0;
    //}
    int Ground0Collided = CheckGround0Collision(&vector_gameobject, dt),
        Ground1Collided = CheckGround1Collision(&vector_gameobject, dt);

    //0 - no collision, 1 - collide from all direction, -1 - collide from left-right , -2 -collide from top-bot 
    if (Ground0Collided == 0 && !Ground1Collided)
        y += dy;
    else if (Ground0Collided == -1 && !Ground1Collided)
    {
        y += dy;
        //vy *= 0.9; // jump slower
    }
        
    //Bug when pushing wall and release

    //Bug when collide with items the same time
    CheckItemCollision(&vector_gameobject, dt);

    ProcessKeyboard();
}

void Aladdin::ProcessKeyboard()
{
    CGame *game = CGame::GetInstance();
    switch (state)
    {
        int direction, updown;
     case ALADDIN_STATE_DEAD: return;
    case ALADDIN_STATE_IDLE:
    case ALADDIN_STATE_RUN:
    case ALADDIN_STATE_IDLE1:
    case ALADDIN_STATE_IDLE2:
    case ALADDIN_STATE_IDLE3:
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
            if (direction > 0)
            {
                SetState(ALADDIN_STATE_RUN);
                vx = ALADDIN_RUNNING_SPEED;
                nx = 1;
            }
            else if (direction < 0)
            {
                SetState(ALADDIN_STATE_RUN);
                vx = -ALADDIN_RUNNING_SPEED;
                nx = -1;
            }
            else
            {
                if(state != ALADDIN_STATE_IDLE && state != ALADDIN_STATE_IDLE1 
                    && state != ALADDIN_STATE_IDLE2 && state != ALADDIN_STATE_IDLE3)
                    SetState(ALADDIN_STATE_IDLE);
            }
        }
        if (game->IsKeyPress(DIK_SPACE)|| game->IsKeyPress(DIK_X))
        {
            if (vx == 0)
                SetState(ALADDIN_STATE_JUMP);
            else
                SetState(ALADDIN_STATE_RUN_JUMP);
        }
        if (game->IsKeyPress(DIK_C))
        {
            SetState(ALADDIN_STATE_ATTACK);
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
		if (game->IsKeyPress(DIK_SPACE) || game->IsKeyPress(DIK_X))
		{
			if (vx == 0)
				SetState(ALADDIN_STATE_JUMP);
			else
				SetState(ALADDIN_STATE_RUN_JUMP);
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
    case ALADDIN_STATE_RUN:
        idle_start = 0;
        break;
    case ALADDIN_STATE_JUMP:
    {
        idle_start = 0;
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
        idle_start = GetTickCount();
        vx = 0;
        break;
    case ALADDIN_STATE_IDLE1:
        animations[ALADDIN_ANI_IDLE1]->ResetAnimation();
        break;
    case ALADDIN_STATE_IDLE2:
        animations[ALADDIN_ANI_IDLE1]->ResetAnimation();
        break;
    case ALADDIN_STATE_IDLE3:
        animations[ALADDIN_ANI_IDLE1]->ResetAnimation();
        break;
    case ALADDIN_STATE_CROUCH:
    {
        idle_start = 0;
        vx = 0;
        animations[ALADDIN_ANI_CROUCH_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_CROUCH_RIGHT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_LOOKUP:
    {
        idle_start = 0;
        vx = 0;
        animations[ALADDIN_ANI_LOOKUP_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_LOOKUP_RIGHT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_ATTACK:
    {
        idle_start = 0;
        animations[ALADDIN_ANI_ATTACK_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_ATTACK_RIGHT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_DEAD:
        idle_start = 0;
        animations[ALADDIN_ANI_DEAD]->ResetAnimation();
        break;
    }
}

void Aladdin::Render()
{
    int restart_frame = 0; //for jump
    if (state == ALADDIN_STATE_DEAD)
    {
        restart_frame = 0;
        //ani = MARIO_ANI_DIE;
    }
    else 
    {
        switch (state)
        {
        case ALADDIN_STATE_IDLE:
        {
            restart_frame = 0;
            if(nx > 0)
                ani = ALADDIN_ANI_IDLE_RIGHT;
            else 
                ani = ALADDIN_ANI_IDLE_LEFT;break;
        }
        case ALADDIN_STATE_RUN:
        {
            restart_frame = 0;
            if (vx > 0)
                ani = ALADDIN_ANI_RUNNING_RIGHT;
            else if (vx < 0)
                ani = ALADDIN_ANI_RUNNING_LEFT;
            break;
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
        case ALADDIN_STATE_IDLE1:
        {
            restart_frame = 1;
            ani = ALADDIN_ANI_IDLE1;
            break;
        }
        case ALADDIN_STATE_IDLE2:
        {
            restart_frame = 6;
            ani = ALADDIN_ANI_IDLE2;
            break;
        }
        case ALADDIN_STATE_IDLE3:
        {
            restart_frame = 0;
            ani = ALADDIN_ANI_IDLE3;
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
        case ALADDIN_STATE_ATTACK:
        {
            restart_frame = 0;
            if (nx > 0)
                ani = ALADDIN_ANI_ATTACK_RIGHT;
            else
                ani = ALADDIN_ANI_ATTACK_LEFT; break;
        }
        }
    }

    int alpha = 255;
    if (untouchable) alpha = 128;
    //animations[ani]->Render(x, y, alpha, restart_frame);
    animations[ani]->Render(x, y, width, lastFrameHeight, alpha, restart_frame, nx);

    //RenderBoundingBox();
}

void Aladdin::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    //width = lastFrameWidth;
    height = lastFrameHeight;

    left = x;
    top = y;
    right = left + width;
    bottom = top - height;
    /*switch (state)
    {
    case ALADDIN_STATE_IDLE:
        right = x + ALADDIN_IDLE_WIDTH;
        bottom = y - ALADDIN_IDLE_HEIGHT;
        break;
    default:
        right = x + ALADDIN_IDLE_WIDTH;
        bottom = y - ALADDIN_IDLE_HEIGHT;
    }*/
}

//0 - no collision, 1 - collide from all direction, -1 - collide from left-right , -2 -collide from top-bot 
int Aladdin::CheckGround0Collision(vector<LPGAMEOBJECT>* coObjects, DWORD dt)
{
    vector<LPCOLLISIONEVENT> coEvents;
    vector<LPCOLLISIONEVENT> coEventsResult;
    coEvents.clear();

    vector<LPGAMEOBJECT> ground0_objects;
    ground0_objects.clear();

    for (UINT i = 0; i < coObjects->size(); i++)
    {
        if (dynamic_cast<Ground *>(coObjects->at(i)) && dynamic_cast<Ground *>(coObjects->at(i))->type == 0)
            ground0_objects.push_back(coObjects->at(i));
    }

    CalcPotentialCollisions(ground0_objects, coEvents);

    // No collision occured, proceed normally
    if (coEvents.size() == 0)
    {
        x += dx;

        // clean up collision events
        for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
        return 0;
    }

    float min_tx, min_ty, nx = 0, ny;
    FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

    // block 
    x += min_tx * dx +nx * 0.2f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
    //y += min_ty * dy + dt*ALADDIN_GRAVITY; //+ ny * 0.2f;

    // clean up collision events
    for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

    if (ny != 0)
    {
        vy = 0;
        if (ny > 0)
            jumping = false;

        if (nx != 0)
        {
            x += min_tx * dx;
            vx = 0;
            return 1;
        }
        else
        {
            return -2;
        }
    }
    else if (nx != 0)
    {
        return -1;
    }
}

bool Aladdin::CheckGround1Collision(vector<LPGAMEOBJECT>* coObjects, DWORD dt)
{
    vector<LPCOLLISIONEVENT> coEvents;
    vector<LPCOLLISIONEVENT> coEventsResult;
    coEvents.clear();

    vector<LPGAMEOBJECT> ground1_objects;
    ground1_objects.clear();

    for (UINT i = 0; i < coObjects->size(); i++)
    {
        if (dynamic_cast<Ground *>(coObjects->at(i)) && dynamic_cast<Ground *>(coObjects->at(i))->type == 1)
            ground1_objects.push_back(coObjects->at(i));
    }

    CalcPotentialCollisions(ground1_objects, coEvents);

    // No collision occured, proceed normally
    if (coEvents.size() == 0)
    {
        // clean up collision events
        for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
        return false;
    }
    else
    {
        float min_tx, min_ty, nx = 0, ny;
        FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

        if (ny > 0)
        {
            vy = 0;
            jumping = false;
            //y += min_ty * dy + ny * 0.2f;
        }
    }

    // clean up collision events
    for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
    return true;
}

bool Aladdin::CheckItemCollision(vector<LPGAMEOBJECT>* coObjects, DWORD dt)
{
    vector<LPCOLLISIONEVENT> coEvents;
    vector<LPCOLLISIONEVENT> coEventsResult;
    coEvents.clear();
    coEventsResult.clear();

    vector<LPGAMEOBJECT> item_objects;
    item_objects.clear();

    for (UINT i = 0; i < coObjects->size(); i++)
    {
        if (dynamic_cast<Apple *>(coObjects->at(i)))
            item_objects.push_back(coObjects->at(i));
    }

    CalcPotentialCollisions(item_objects, coEvents);

    // No collision occured, proceed normally
    if (coEvents.size() == 0)
    {
        // clean up collision events
        for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
        return false;
    }
    else
    {
        DebugOut(L"Va cham1\n");
        float min_tx, min_ty, nx = 0, ny;
        FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

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
    }

    // clean up collision events
    for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
    return true;
}

//void Aladdin::FilterGroundCollision0(
//    vector<LPCOLLISIONEVENT> &coEvents,
//    vector<LPCOLLISIONEVENT> &coEventsResult,
//    float &min_tx, float &min_ty,
//    float &nx, float &ny)
//{
//    min_tx = 1.0f;
//    min_ty = 1.0f;
//    int min_ix = -1;
//    int min_iy = -1;
//
//    nx = 0.0f;
//    ny = 0.0f;
//
//    coEventsResult.clear();
//
//    for (UINT i = 0; i < coEvents.size(); i++)
//    {
//        LPCOLLISIONEVENT c = coEvents[i];
//        
//        if (dynamic_cast<Ground *>(c->obj) && dynamic_cast<Ground *>(c->obj)->type == 0)
//        {
//            /*if (dynamic_cast<Ground *>(c->obj)->type == 0)
//                c->type = 0;
//            else
//                c->type = 1;*/
//            if (c->t < min_tx && c->nx != 0) {
//                min_tx = c->t; nx = c->nx; min_ix = i;
//            }
//
//            if (c->t < min_ty  && c->ny != 0) {
//                min_ty = c->t; ny = c->ny; min_iy = i;
//            }
//        }
//    }
//
//    if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
//    if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
//}
//
//void Aladdin::FilterGroundCollision1(
//    vector<LPCOLLISIONEVENT> &coEvents,
//    vector<LPCOLLISIONEVENT> &coEventsResult,
//    float &min_tx, float &min_ty,
//    float &nx, float &ny)
//{
//    min_tx = 1.0f;
//    min_ty = 1.0f;
//    int min_ix = -1;
//    int min_iy = -1;
//
//    nx = 0.0f;
//    ny = 0.0f;
//
//    coEventsResult.clear();
//
//    for (UINT i = 0; i < coEvents.size(); i++)
//    {
//        LPCOLLISIONEVENT c = coEvents[i];
//
//        if (dynamic_cast<Ground *>(c->obj) && dynamic_cast<Ground *>(c->obj)->type == 1)
//        {
//            /*if (dynamic_cast<Ground *>(c->obj)->type == 0)
//                c->type = 0;
//            else
//                c->type = 1;*/
//            if (c->t < min_tx && c->nx != 0) {
//                min_tx = c->t; nx = c->nx; min_ix = i;
//            }
//
//            if (c->t < min_ty  && c->ny != 0) {
//                min_ty = c->t; ny = c->ny; min_iy = i;
//            }
//        }
//    }
//
//    if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
//    if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
//}
//
//void Aladdin::FilterItemCollision(
//    vector<LPCOLLISIONEVENT> &coEvents,
//    vector<LPCOLLISIONEVENT> &coEventsResult,
//    float &min_tx, float &min_ty,
//    float &nx, float &ny)
//{
//    min_tx = 1.0f;
//    min_ty = 1.0f;
//    int min_ix = -1;
//    int min_iy = -1;
//
//    nx = 0.0f;
//    ny = 0.0f;
//
//    coEventsResult.clear();
//
//    for (UINT i = 0; i < coEvents.size(); i++)
//    {
//        LPCOLLISIONEVENT c = coEvents[i];
//
//        if (dynamic_cast<Apple *>(c->obj))
//        {
//            if (c->t < min_tx && c->nx != 0) {
//                min_tx = c->t; nx = c->nx; min_ix = i;
//            }
//
//            if (c->t < min_ty  && c->ny != 0) {
//                min_ty = c->t; ny = c->ny; min_iy = i;
//            }
//        }
//    }
//
//    if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
//    if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
//}