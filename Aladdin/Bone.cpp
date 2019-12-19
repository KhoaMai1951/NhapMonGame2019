#include "Bone.h"

void Bone::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}

void Bone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (isDead) return;
    ViewPort* cam = ViewPort::getInstance();
    RECT cam_rect = cam->getBounding();
    if (!checkOverlap(x, y, x + width, y - height, cam_rect.left, cam_rect.top, cam_rect.right, cam_rect.bottom))
    {
        isDead = true;
        return;
    }
	if (GetTickCount() - create_start > AUTO_DESTROY_TIME)
	{
		isDead = true;
		return;
	}
	if (hitpoint <= 0 && state != BONE_STATE_DEAD)
	{
        SetState(BONE_STATE_DEAD);
        return;
	}
    else if (state == BONE_STATE_DEAD)
    {
        if (animations[ani]->currentFrame == 9)
            isDead = true;
        return;
    }

	CGameObject::Update(dt);

	vx += BONE_SPEED * dt * nx;
	vy -= dt * BONE_GRAVITY;

#pragma region
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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*>(e->obj))
			{
				if (nx != 0)
				{
					vx = -vx;
				}
				if (ny != 0)
					vy = -vy;
				// block 
				x += min_tx * dx + nx * 0.1f;
				y += min_ty * dy + ny * 0.1f;
                Sound::getInstance()->play("BONE_DROP", false, 1);
			}
		}
		x += vx;
		y += vy;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion collision

}

void Bone::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BONE_STATE_FLYING:
        ani = BONE_ANI_FLYING; break;
    case BONE_STATE_DEAD:
        vx = 0; vy = 0;
		break;
	}
}

void Bone::Render()
{
    if (state == BONE_STATE_DEAD)
        ani = BONE_ANI_DEAD;
	if(!isDead)
        animations[ani]->Render(x, y);
	//DebugOut(L"Rendering bones \n");
}