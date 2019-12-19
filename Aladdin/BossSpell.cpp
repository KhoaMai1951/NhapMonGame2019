//#include "BossSpell.h"
//
//void BossSpell::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	if (nx == -1)
//		left = x + 10;
//	else
//		left = x;
//	top = y - 18;
//	right = left + width;
//	bottom = top - height;
//}
//
//void BossSpell::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	if (isDead) return;
//	ViewPort* cam = ViewPort::getInstance();
//	RECT cam_rect = cam->getBounding();
//
//	CGameObject::Update(dt);
//
//	vy = 0;
//
//	vx = BOSS_SPELL_SPEED * dt * nx;
//
//#pragma region
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;
//
//	float l, t, r, b;
//	GetBoundingBox(l, t, r, b);
//	set<CGameObject*> set_gameobject = SpatialGrid::GetInstance()->GetGridForCollision(l, t, r, b);
//	vector<CGameObject*> vector_gameobject(set_gameobject.begin(), set_gameobject.end());
//
//	coEvents.clear();
//
//	//void CGameObject::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
//	CalcPotentialCollisions(vector_gameobject, coEvents);
//
//	// No collision occured, proceed normally
//	if (coEvents.size() == 0)
//	{
//		x += vx;
//		y += vy;
//	}
//	else
//	{
//		float min_tx, min_ty, nx = 0, ny;
//
//		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
//
//		for (UINT i = 0; i < coEventsResult.size(); i++)
//		{
//			LPCOLLISIONEVENT e = coEventsResult[i];
//
//
//		}
//		x += vx;
//		y += vy;
//	}
//
//	// clean up collision events
//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
//#pragma endregion collision
//
//}
//
//void BossSpell::SetState(int state)
//{
//	BossSpell::SetState(state);
//	switch (state)
//	{
//
//	}
//}
//
//void BossSpell::Render()
//{
//	/*if (nx > 0)
//	{
//		ani = BOSS_FLAME_ANI_RUNNING_RIGHT;
//	}
//	else ani = BOSS_FLAME_ANI_RUNNING_LEFT;
//*/
//	animations[ani]->Render(x, y);
//	RenderBoundingBox();
//}