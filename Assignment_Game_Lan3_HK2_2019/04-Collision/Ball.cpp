#include <algorithm>
#include "debug.h"

#include "Ball.h"
#include "Game.h"

#include "Bar.h"

#include <time.h>
#include <stdio.h>

float CBall::Random(int min, int max)
{
    srand((int)time(0));
    int r = min + rand() % (max + 1 - min);
    while (r <= max/3 && r >= -max/3)
    {
        r = min + rand() % (max + 1 - min);
    }
    return r;
}

void CBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
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
	/*x += dx;
	y += dy;*/

	//Bouncing		
	if (y < 0 || y>240-55)
	{
		vy = -vy;
		y = y + vy;
	}

    //Reset
    if (x <= 0)
    {
        CGame::GetInstance()->increasePointP2();
        this->SetPosition(320 / 2 - 10, 240 / 2 - 40);
        this->SetState(BALL_IDLE);
    }
    else if (x >= 320 - 30)
    {
        CGame::GetInstance()->increasePointP1();
        this->SetPosition(320 / 2 - 10, 240 / 2 - 40);
        this->SetState(BALL_IDLE);
    }
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// Collision logic with Bar
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBar*>(e->obj))  // if e->obj is BAR
			{
				CBar* bar = dynamic_cast<CBar*>(e->obj);
                if (vx < 0 && vy > 0)
                {
                    vx = -vx;
                }
                else if (vy < 0 && vx < 0)
                {
                    vx = -vx;
                }
                else if (vy < 0 && vx > 0)
                {
                    vx = -vx;
                }
                else if (vy > 0 && vx > 0)
                {
                    vx = -vx;
                }
				
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBall::SetState(int state)
{
	CGameObject::SetState(state);

    switch (state)
    {
        case BALL_MOVING:
        {
           /* vx = BALL_MOVE_SPEED * Random(-1, 1);
            vy = BALL_MOVE_SPEED * Random(-10, 10)*0.1;*/
			vx = -BALL_MOVE_SPEED;
			vy = 0;
            break;
        }
        case BALL_IDLE:
        {
            vx = 0;
            vy = 0;
            break;
        }
    }
}

void CBall::Render()
{
	int ani = 0;

	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(x, y, alpha);

	//Vẽ ra BoundingBox
	//RenderBoundingBox();
}

void CBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = x + BALL_BBOX_WIDTH;
	bottom = y + BALL_BBOX_HEIGHT;
}

