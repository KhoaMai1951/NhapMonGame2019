#include "Aladdin.h"
#include "SultansDungeon_Scene.h"

void Aladdin::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
    // turn off collision when die 
    if (state == ALADDIN_STATE_DEAD)
    {
        if (CGame::GetInstance()->IsKeyPress(DIK_Q))
        {
            SetState(ALADDIN_STATE_IDLE);
            vx = 0; nx = 1;
        }
        return;
    }
    // Calculate dx, dy 
    CGameObject::Update(dt);

    // Simple fall down
	if(state != ALADDIN_STATE_CLIMB)
		vy -= ALADDIN_GRAVITY * dt;

#pragma region
    if (state == ALADDIN_STATE_IDLE)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 5000)
        {
            SetState(ALADDIN_STATE_IDLE1);
        }
    }
    else if (state == ALADDIN_STATE_ATTACK)
    {
        if (animations[ani]->currentFrame == 5)
            SetState(ALADDIN_STATE_IDLE);
    }
    else if (state == ALADDIN_STATE_SIT_ATTACK)
    {
        if (animations[ani]->currentFrame == 6)
        {
            SetState(ALADDIN_STATE_CROUCH);
            if (nx > 0)
                animations[ALADDIN_ANI_CROUCH_RIGHT]->currentFrame = 3;
            else if (nx < 0)
                animations[ALADDIN_ANI_CROUCH_LEFT]->currentFrame = 3;
        }      
    }
    else if (state == ALADDIN_STATE_RUN_ATTACK)
    {
        if (animations[ani]->currentFrame == 6)
            SetState(ALADDIN_STATE_RUN);
    }
    else if (state == ALADDIN_STATE_THROW_APPLE)
    {
        if (animations[ani]->currentFrame == 3)
        {
            AddThrowApple();
        }
        else if (animations[ani]->currentFrame == 4)
            throwing = false;
        else if (animations[ani]->currentFrame == 6)
        {
            SetState(ALADDIN_STATE_IDLE);
        }

    }
    else if (state == ALADDIN_STATE_RUN_THROW)
    {
        if (animations[ani]->currentFrame == 3)
        {
            AddThrowApple();
        }
        else if (animations[ani]->currentFrame == 4)
            throwing = false;
        else if (animations[ani]->currentFrame == 6)
        {
            SetState(ALADDIN_STATE_RUN);
        }

    }
    else if (state == ALADDIN_STATE_SIT_THROW)
    {
        if (animations[ani]->currentFrame == 2)
        {
            AddThrowApple();
        }
        else if (animations[ani]->currentFrame == 3)
            throwing = false;
        else if (animations[ani]->currentFrame == 5)
        {
            SetState(ALADDIN_STATE_CROUCH);
            if (nx > 0)
                animations[ALADDIN_ANI_CROUCH_RIGHT]->currentFrame = 3;
            else if (nx < 0)
                animations[ALADDIN_ANI_CROUCH_LEFT]->currentFrame = 3;
        }
            
    }
    else if (state == ALADDIN_STATE_JUMP_THROW)
    {
        if (animations[ani]->currentFrame == 2)
        {
            AddThrowApple();
        }
        else if (animations[ani]->currentFrame == 3)
            throwing = false;

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
	else if (state == ALADDIN_STATE_CLIMB)
	{
		//vx = 0;
		////vy += ALADDIN_GRAVITY * dt;
		//vy = 0;
	}
#pragma endregion Check State
	

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

    //// turn off collision when die 
    //if (state == ALADDIN_STATE_DEAD)
    //{
    //    if (CGame::GetInstance()->IsKeyPress(DIK_Q))
    //    {
    //        SetState(ALADDIN_STATE_IDLE);
    //        vx = 0; nx = 1;
    //    }
    //    return;
    //}
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

	if (CheckChainCollision(&vector_gameobject, dt))
	{
		y += dy;
	}


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
            else if(direction < 0)
                nx = -1;
            if (state != ALADDIN_STATE_CROUCH)
                SetState(ALADDIN_STATE_CROUCH);
            //sit attack
            if (game->IsKeyPress(DIK_C))
            {
                SetState(ALADDIN_STATE_SIT_ATTACK);
            }
            //sit throw
            else if (game->IsKeyPress(DIK_V))
            {
                if(!throwing)
                    SetState(ALADDIN_STATE_SIT_THROW);
            }
        }
        else
        {
            if (direction > 0)
            {
                if (pushing == 0)
                {
                    SetState(ALADDIN_STATE_RUN);
                    vx = ALADDIN_RUNNING_SPEED;
                }
                else if (pushing == 0)
                {
                    SetState(ALADDIN_STATE_PUSH);
                }
                
                nx = 1;

                //run attack
                if (game->IsKeyPress(DIK_C))
                {
                    SetState(ALADDIN_STATE_RUN_ATTACK);
                }
                //run throw
                else if (game->IsKeyPress(DIK_V))
                {
                    if (!throwing)
                        SetState(ALADDIN_STATE_RUN_THROW);
                }
            }
            else if (direction < 0)
            {
                if (pushing == 0)
                {
                    SetState(ALADDIN_STATE_RUN);
                    vx = -ALADDIN_RUNNING_SPEED;
                }
                else if (pushing == 0)
                {
                    SetState(ALADDIN_STATE_PUSH);
                }
                nx = -1;

                //run attack
                if (game->IsKeyPress(DIK_C))
                {
                    SetState(ALADDIN_STATE_RUN_ATTACK);
                }
                //run throw
                else if (game->IsKeyPress(DIK_V))
                {
                    if (!throwing)
                        SetState(ALADDIN_STATE_RUN_THROW);
                }
            }
            else
            {
                if(state != ALADDIN_STATE_IDLE && state != ALADDIN_STATE_IDLE1 
                    && state != ALADDIN_STATE_IDLE2 && state != ALADDIN_STATE_IDLE3)
                    SetState(ALADDIN_STATE_IDLE);
            }
            //stand attack
            if (game->IsKeyPress(DIK_C))
            {
                if (vx == 0)
                    SetState(ALADDIN_STATE_ATTACK);
            }
            //stand throw
            else if (game->IsKeyPress(DIK_V))
            {
                if (!throwing)
                    if (vx == 0) SetState(ALADDIN_STATE_THROW_APPLE);
            }
        }
        if (game->IsKeyPress(DIK_SPACE)|| game->IsKeyPress(DIK_X))
        {
            if (vx == 0)
                SetState(ALADDIN_STATE_JUMP);
            else
                SetState(ALADDIN_STATE_RUN_JUMP);
        }
        //stuck breaker
        else if (game->IsKeyPress(DIK_Q))
        {
            SetState(ALADDIN_STATE_IDLE);
            nx = 1;
            vx = 0;
            jumping = false;
            climbing = false;
            throwing = false;
            pushing = 0;
        }
        //Dead
        else if (game->IsKeyPress(DIK_P))
        {
            SetState(ALADDIN_STATE_DEAD);
            vy = 0;
            vx = 0;
        }
        return;
    }
    case ALADDIN_STATE_PUSH:
    {
        direction = game->IsKeyDown(DIK_RIGHT) - game->IsKeyDown(DIK_LEFT);
        if (direction > 0)
        {
            if (pushing == -1)
            {
                nx = 1;
                SetState(ALADDIN_STATE_RUN);
                vx = ALADDIN_RUNNING_SPEED;
                width = ALADDIN_IDLE_WIDTH;
            }
        }
        else if (direction < 0)
        {
            if (pushing == 1)
            {
                nx = -1;
                SetState(ALADDIN_STATE_RUN);
                vx = -ALADDIN_RUNNING_SPEED;
                pushing = false;
                width = ALADDIN_IDLE_WIDTH;
            }
        }
        else //direction == 0
        {
            pushing = false;
            SetState(ALADDIN_STATE_IDLE);
            width = ALADDIN_IDLE_WIDTH;
            if (nx > 0)
            {
                x += ALADDIN_PUSH_WIDTH - ALADDIN_IDLE_WIDTH;
            }
        }
        return;
    }
    case ALADDIN_STATE_JUMP: 
    case ALADDIN_STATE_RUN_JUMP:
    case ALADDIN_STATE_JUMP_ATTACK:
    case ALADDIN_STATE_JUMP_THROW:
    {
        if (!jumping)
        {
            //state = ALADDIN_STATE_IDLE;
            SetState(ALADDIN_STATE_IDLE);
            return;
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
        if (game->IsKeyPress(DIK_C))
        {
            SetState(ALADDIN_STATE_JUMP_ATTACK);
        }
        else if (game->IsKeyPress(DIK_V))
        {
            if (!throwing)
                SetState(ALADDIN_STATE_JUMP_THROW);
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
	case ALADDIN_STATE_CLIMB:
	{
		if (this->y <= climbingChains->bot)
		{
			SetState(ALADDIN_STATE_IDLE);
			climbingChains = NULL;
			//climbing = false;
			return;
		}
		else if (game->IsKeyDown(DIK_UP) && this->y < climbingChains->y - 15)
		{
				vy = ALADDIN_CLIMB_SPEED;
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			vy = -ALADDIN_CLIMB_SPEED;
		}
		else
		{
			vy = 0;
		}
		if (game->IsKeyPress(DIK_W))
		{
			x += 100;
			if (vx == 0)
				SetState(ALADDIN_STATE_IDLE);
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

        //Lấy rect Aladdin
        float l, t, r, b;
        GetBoundingBox(l, t, r, b);
        l -= THROW_SIZE;
        t += THROW_SIZE;
        r += THROW_SIZE;
        b -= THROW_SIZE;
        //Lấy các obj thuộc các lưới có chứa player
        RECT temp = ViewPort::getInstance()->InvertY(l, t, r, b, SCREEN_WIDTH, SCREEN_HEIGHT);
        set<CGameObject*> objects = SpatialGrid::GetInstance()->GetGridForCollision(temp.left,
            temp.top, temp.right, temp.bottom);

        vector<CGameObject*> vector_object(objects.begin(), objects.end());

        CheckAttackCollision(vector_object);

        break;
    }
    case ALADDIN_STATE_RUN_ATTACK:
    {
        idle_start = 0;
        animations[ALADDIN_ANI_RUN_ATTACK_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_RUN_ATTACK_RIGHT]->ResetAnimation();

        //Lấy rect Aladdin
        float l, t, r, b;
        GetBoundingBox(l, t, r, b);
        l -= THROW_SIZE;
        t += THROW_SIZE;
        r += THROW_SIZE;
        b -= THROW_SIZE;
        //Lấy các obj thuộc các lưới có chứa player
        RECT temp = ViewPort::getInstance()->InvertY(l, t, r, b, SCREEN_WIDTH, SCREEN_HEIGHT);
        set<CGameObject*> objects = SpatialGrid::GetInstance()->GetGridForCollision(temp.left,
            temp.top, temp.right, temp.bottom);

        vector<CGameObject*> vector_object(objects.begin(), objects.end());

        CheckAttackCollision(vector_object);

        break;
    }
    case ALADDIN_STATE_JUMP_ATTACK:
    {
        idle_start = 0;
        animations[ALADDIN_ANI_JUMP_ATTACK_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_JUMP_ATTACK_RIGHT]->ResetAnimation();

        //Lấy rect Aladdin
        float l, t, r, b;
        GetBoundingBox(l, t, r, b);
        l -= THROW_SIZE;
        t += THROW_SIZE;
        r += THROW_SIZE;
        b -= THROW_SIZE;
        //Lấy các obj thuộc các lưới có chứa player
        RECT temp = ViewPort::getInstance()->InvertY(l, t, r, b, SCREEN_WIDTH, SCREEN_HEIGHT);
        set<CGameObject*> objects = SpatialGrid::GetInstance()->GetGridForCollision(temp.left,
            temp.top, temp.right, temp.bottom);

        vector<CGameObject*> vector_object(objects.begin(), objects.end());

        CheckAttackCollision(vector_object);
        break;
    }
    case ALADDIN_STATE_SIT_ATTACK:
    {
        idle_start = 0;
        animations[ALADDIN_ANI_SIT_ATTACK_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_SIT_ATTACK_RIGHT]->ResetAnimation();

        //Lấy rect Aladdin
        float l, t, r, b;
        GetBoundingBox(l, t, r, b);
        l -= THROW_SIZE;
        t += THROW_SIZE;
        r += THROW_SIZE;
        b -= THROW_SIZE;
        //Lấy các obj thuộc các lưới có chứa player
        RECT temp = ViewPort::getInstance()->InvertY(l, t, r, b, SCREEN_WIDTH, SCREEN_HEIGHT);
        set<CGameObject*> objects = SpatialGrid::GetInstance()->GetGridForCollision(temp.left,
            temp.top, temp.right, temp.bottom);

        vector<CGameObject*> vector_object(objects.begin(), objects.end());

        CheckAttackCollision(vector_object);

        break;
    }
    case ALADDIN_STATE_THROW_APPLE:
    {
        idle_start = 0;
        animations[ALADDIN_ANI_THROW_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_THROW_RIGHT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_SIT_THROW:
    {
        idle_start = 0;
        animations[ALADDIN_ANI_SIT_THROW_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_SIT_THROW_RIGHT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_RUN_THROW:
    {
        idle_start = 0;
        animations[ALADDIN_ANI_RUN_THROW_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_RUN_THROW_RIGHT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_JUMP_THROW:
    {
        idle_start = 0;
        animations[ALADDIN_ANI_JUMP_THROW_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_JUMP_THROW_RIGHT]->ResetAnimation();
        break;
    }
    case ALADDIN_STATE_PUSH:
        idle_start = 0;
        animations[ALADDIN_ANI_PUSHING_LEFT]->ResetAnimation();
        animations[ALADDIN_ANI_PUSHING_RIGHT]->ResetAnimation();
        width = ALADDIN_PUSH_WIDTH;
        if (nx > 0)
            x -= ALADDIN_PUSH_WIDTH - ALADDIN_IDLE_WIDTH;
        break;
    case ALADDIN_STATE_DEAD:
        idle_start = 0;
        animations[ALADDIN_ANI_DEAD]->ResetAnimation();
        break;
	case ALADDIN_STATE_CLIMB:
		idle_start = 0;
		vx = 0;
		vy = 0;
		//animations[ALADDIN_ANI_DEAD]->ResetAnimation();
		break;
    }
}

void Aladdin::Render()
{
    int restart_frame = 0; //for jump
    if (state == ALADDIN_STATE_DEAD)
    {
        restart_frame = 0;
        ani = ALADDIN_ANI_DEAD;
    }
    else 
    {
		switch (state)
		{
		case ALADDIN_STATE_IDLE:
		{
			restart_frame = 0;
			if (nx > 0)
				ani = ALADDIN_ANI_IDLE_RIGHT;
			else
				ani = ALADDIN_ANI_IDLE_LEFT; break;
		}
		case ALADDIN_STATE_RUN:
		{
			restart_frame = 3;
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
		case ALADDIN_STATE_RUN_ATTACK:
		{
			restart_frame = 0;
			if (nx > 0)
				ani = ALADDIN_ANI_RUN_ATTACK_RIGHT;
			else
				ani = ALADDIN_ANI_RUN_ATTACK_LEFT; break;
		}
		case ALADDIN_STATE_JUMP_ATTACK:
		{
			restart_frame = 6;
			if (nx > 0)
				ani = ALADDIN_ANI_JUMP_ATTACK_RIGHT;
			else
				ani = ALADDIN_ANI_JUMP_ATTACK_LEFT; break;
		}
		case ALADDIN_STATE_SIT_ATTACK:
		{
			restart_frame = 0;
			if (nx > 0)
				ani = ALADDIN_ANI_SIT_ATTACK_RIGHT;
			else
				ani = ALADDIN_ANI_SIT_ATTACK_LEFT; break;
		}
		case ALADDIN_STATE_THROW_APPLE:
		{
			restart_frame = 0;
			if (nx > 0)
				ani = ALADDIN_ANI_THROW_RIGHT;
			else
				ani = ALADDIN_ANI_THROW_LEFT; break;
		}
		case ALADDIN_STATE_RUN_THROW:
		{
			restart_frame = 0;
			if (nx > 0)
				ani = ALADDIN_ANI_RUN_THROW_RIGHT;
			else
				ani = ALADDIN_ANI_RUN_THROW_LEFT; break;
		}
		case ALADDIN_STATE_JUMP_THROW:
		{
			restart_frame = 5;
			if (nx > 0)
				ani = ALADDIN_ANI_JUMP_THROW_RIGHT;
			else
				ani = ALADDIN_ANI_JUMP_THROW_LEFT; break;
		}
		case ALADDIN_STATE_SIT_THROW:
		{
			restart_frame = 0;
			if (nx > 0)
				ani = ALADDIN_ANI_SIT_THROW_RIGHT;
			else
				ani = ALADDIN_ANI_SIT_THROW_LEFT; break;
		}
		case ALADDIN_STATE_PUSH:
		{
			restart_frame = 2;
			if (nx > 0)
				ani = ALADDIN_ANI_PUSHING_RIGHT;
			else
				ani = ALADDIN_ANI_PUSHING_LEFT; break;
		}
		case ALADDIN_STATE_CLIMB:
		{
			ani = ALADDIN_ANI_CLIMB_ROPE;
			break;
		}
		case ALADDIN_STATE_CLIMB_UP:
		{
			ani = ALADDIN_ANI_CLIMB_ROPE;
			break;
		}
		}
    }

    int alpha = 255;
    if (untouchable) alpha = 128;
    //animations[ani]->Render(x, y, alpha, restart_frame);
    animations[ani]->Render(x, y, width, lastFrameHeight, alpha, restart_frame, nx);

    RenderBoundingBox();
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
        try
        {
            if (dynamic_cast<Ground *>(coObjects->at(i)))
            {
                if (dynamic_cast<Ground *>(coObjects->at(i))->type == 0)
                    ground0_objects.push_back(coObjects->at(i));
            }
        }
        catch (exception e)
        {
            DebugOut(L"Caused exception\n");
            continue;
        }    
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
            if (state == ALADDIN_STATE_RUN || state == ALADDIN_STATE_IDLE)
            {
                if (nx > 0)
                    pushing = -1;
                else
                    pushing = 1;
                if (state != ALADDIN_STATE_PUSH)
                    SetState(ALADDIN_STATE_PUSH);
            }
            return 1;
        }
        else
        {
            return -2;
        }
    }
    else if (nx != 0)
    {
        if (state == ALADDIN_STATE_RUN || state == ALADDIN_STATE_IDLE)
        {
            if (nx > 0)
                pushing = -1;
            else
                pushing = 1;
            if (state != ALADDIN_STATE_PUSH)
                SetState(ALADDIN_STATE_PUSH);
        }
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
        try
        {
            if (dynamic_cast<Ground *>(coObjects->at(i)) && dynamic_cast<Ground *>(coObjects->at(i))->type == 1)
                ground1_objects.push_back(coObjects->at(i));
        }
        catch (exception e)
        {
            DebugOut(L"Caused exception\n");
            continue;
        }
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
        //if (dynamic_cast<Apple *>(coObjects->at(i)))
        //    item_objects.push_back(coObjects->at(i));
        if (coObjects->at(i)->isItem == true)
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
            else if (dynamic_cast<Ruby *>(e->obj))
            {
                Ruby *ruby = dynamic_cast<Ruby *>(e->obj);

                if (e->ny != 0 || e->nx != 0)
                {
                    if (ruby->GetState() != RUBY_STATE_EATEN)
                    {
                        ruby->SetState(RUBY_STATE_EATEN);
                    }
                }
            }
           /* else if (dynamic_cast<Genie *>(e->obj))
            {
                Genie *genie = dynamic_cast<Genie *>(e->obj);

                if (e->ny != 0 || e->nx != 0)
                {
                    if (genie->GetState() != GENIE_STATE_EATEN)
                    {
                        genie->SetState(GENIE_STATE_EATEN);
                    }
                }
            }*/
            else if (dynamic_cast<Vase *>(e->obj))
            {
                Vase *vase = dynamic_cast<Vase *>(e->obj);

                if (e->ny != 0 || e->nx != 0)
                {
                    if (vase->GetState() != VASE_STATE_EATEN)
                    {
                        vase->SetState(VASE_STATE_EATEN);
                    }
                }
            }
            else if (dynamic_cast<LifeHeal *>(e->obj))
            {
                LifeHeal *life = dynamic_cast<LifeHeal *>(e->obj);

                if (e->ny != 0 || e->nx != 0)
                {
                    if (life->GetState() != LIFEHEAL_STATE_EATEN)
                    {
                        life->SetState(LIFEHEAL_STATE_EATEN);
                    }
                }
            }
        }
    }

    // clean up collision events
    for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
    return true;
}

bool Aladdin::checkOverlap(float l1, float t1, float r1, float b1, float l2, float t2, float r2, float b2)
{
    //Check horizontal aspect
    if (l1 > r2 || l2 > r1)
        return false;

    //Check vertical aspect
    if (t1 < b2 || t2 < b1)
        return false;

    return true;
}

void Aladdin::CheckAttackCollision(vector<LPGAMEOBJECT> atkCol_object)
{

    for (UINT i = 0; i < atkCol_object.size(); i++)
    {
        int attack_size = 0;
        if (dynamic_cast<Enemy*>(atkCol_object.at(i)))
        {
            Enemy* enemy = dynamic_cast<Enemy*>(atkCol_object.at(i));

            //Lấy rect enemy
            float l1 = enemy->x;
            float t1 = enemy->y;
            float r1 = l1 + enemy->width;
            float b1 = t1 - enemy->height;

            //Lấy bbox của attack animation
            float l2, t2, r2, b2;
            switch (state)
            {
            case ALADDIN_STATE_ATTACK: 
                attack_size = ATTACK_SIZE; break;
            case ALADDIN_STATE_SIT_ATTACK:
                attack_size = SIT_ATTACK_SIZE; break;
            case ALADDIN_STATE_JUMP_ATTACK:
                attack_size = JUMP_ATTACK_SIZE; break;
            case ALADDIN_STATE_RUN_ATTACK:
                attack_size = RUN_ATTACK_SIZE; break;
            }
            if (nx >= 1)
            {
                l2 = x;
                t2 = y;
                r2 = l2 + width + attack_size;
                b2 = t2 - height;
            }
            if (nx <= -1)
            {
                l2 = x - attack_size;
                t2 = y;
                r2 = l2 + width;
                b2 = t2 - height;
            }


            if (checkOverlap(l1, t1, r1, b1, l2, t2, r2, b2))
            {
                //guard0->SetState(STATE_HURT);
                //enemy->hitpoint--;
                DebugOut(L"Enemy overlap \n");
            }
        }
    }
}

void Aladdin::AddThrowApple()
{
    if (!throwing)
    {
        //nem tao
        ThrowApple* throwApple = new ThrowApple();
        throwApple->name = "throw_apple";
        throwApple->AddAnimation(ANI_APPLE_FLYING);
        throwApple->AddAnimation(ANI_APPLE_DESTROY);
        throwApple->nx = nx;
        float temp_x;
        if (nx >= 0)
        {
            temp_x = x + width - 12;
        }
        else
        {
            temp_x = x + 12;
        }
        throwApple->SetPosition(temp_x, y - 5);
        throwApple->SetState(THROW_APPLE_STATE_FLYING);
        ((SultansDungeon_Scene*)scene)->vector_apple.push_back(throwApple);
        throwing = true;
    }
}

bool Aladdin::CheckChainCollision(vector<LPGAMEOBJECT>* coObjects, DWORD dt)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	coEventsResult.clear();

	vector<LPGAMEOBJECT> item_objects;
	item_objects.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		//if (dynamic_cast<Apple *>(coObjects->at(i)))
		//    item_objects.push_back(coObjects->at(i));
		item_objects.push_back(coObjects->at(i));
	}

	CalcPotentialCollisions(item_objects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Chains*>(e->obj)) // if e->obj is Chain
			{
				Chains* chain = dynamic_cast<Chains*>(e->obj);
				if (state != ALADDIN_STATE_CLIMB)
				{
					this->x = chain->x - 15;
					SetState(ALADDIN_STATE_CLIMB);
					climbingChains = chain;
					y += 6;
				}
				return true;
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	return false;
}