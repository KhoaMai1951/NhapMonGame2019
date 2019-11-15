#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include <set>
#include "SpatialGrid.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy -= MARIO_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	//Lấy các obj thuộc các lưới có chứa player
	set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->Get(l, t, r, b);

	//Truyền set các obj thuộc các lưới có player vào vector
	vector<CGameObject*> vector_gameobject(set_gameobject.begin(), set_gameobject.end());

	coEvents.clear();

	// turn off collision when die 
	//void CGameObject::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(vector_gameobject, coEvents);

	////test grid
	//for (UINT i = 0; i < vector_gameobject.size(); i++)
	//{
	//	CGameObject* e = vector_gameobject.at(i);

	//	if (e->name == "Goomba") // if e->obj is Goomba 
	//	{
	//		DebugOut(L"Goomba id so: %d\n",e->id);
	//	}
	//}

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else 
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

    ProcessKeyboard();
}

void CMario::ProcessKeyboard()
{
    CGame *game = CGame::GetInstance();
    switch (state)
    {
        int direction;
    case MARIO_STATE_DIE: return;
    case MARIO_STATE_IDLE:
        direction = game->IsKeyDown(DIK_RIGHT) - game->IsKeyDown(DIK_LEFT);
        if (direction > 0)
        {
            SetState(MARIO_STATE_WALKING_RIGHT);
        }
        else if (direction < 0)
        {
            SetState(MARIO_STATE_WALKING_LEFT);
        }
        else
        {
            SetState(MARIO_STATE_IDLE);
        }
        if (game->IsKeyPress(DIK_SPACE))
            SetState(MARIO_STATE_JUMP);
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
    case MARIO_STATE_WALKING_RIGHT:
        direction = game->IsKeyDown(DIK_RIGHT) - game->IsKeyDown(DIK_LEFT);
        if (direction > 0)
        {
            SetState(MARIO_STATE_WALKING_RIGHT);
        }
        else if (direction < 0)
        {
            SetState(MARIO_STATE_WALKING_LEFT);
        }
        else
        {
            SetState(MARIO_STATE_IDLE);
        }
        if (game->IsKeyPress(DIK_SPACE))
            SetState(MARIO_STATE_JUMP);
        return;
    case MARIO_STATE_WALKING_LEFT:
        direction = game->IsKeyDown(DIK_RIGHT) - game->IsKeyDown(DIK_LEFT);
        if (direction > 0)
        {
            SetState(MARIO_STATE_WALKING_RIGHT);
        }
        else if (direction < 0)
        {
            SetState(MARIO_STATE_WALKING_LEFT);
        }
        else
        {
            SetState(MARIO_STATE_IDLE);
        }
        if (game->IsKeyPress(DIK_SPACE))
            SetState(MARIO_STATE_JUMP);
        return;
    case MARIO_STATE_JUMP:
        direction = game->IsKeyDown(DIK_RIGHT) - game->IsKeyDown(DIK_LEFT);
        if (direction > 0)
        {
            SetState(MARIO_STATE_WALKING_RIGHT);
        }
        else if (direction < 0)
        {
            SetState(MARIO_STATE_WALKING_LEFT);
        }
        else
        {
            SetState(MARIO_STATE_IDLE);
        }
        if (game->IsKeyPress(DIK_SPACE))
            SetState(MARIO_STATE_JUMP);
        return;
    }

}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP: 
		vy = MARIO_JUMP_SPEED_Y;
	case MARIO_STATE_IDLE: 
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::Render()
{
	int ani;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
				else ani = MARIO_ANI_BIG_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = MARIO_ANI_BIG_WALKING_RIGHT;
			else ani = MARIO_ANI_BIG_WALKING_LEFT;
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				else ani = MARIO_ANI_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = MARIO_ANI_SMALL_WALKING_RIGHT;
			else ani = MARIO_ANI_SMALL_WALKING_LEFT;
		}

	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(x, y, alpha);

	RenderBoundingBox();
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level==MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y - MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y - MARIO_SMALL_BBOX_HEIGHT;
	}
}

