#include "BossSpell.h"

void BossSpell::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
    top = y;
	right = left + width;
	bottom = top - height;
}

void BossSpell::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDead) return;
    if (x < 80 || x > BOSS_MAP_WIDTH - 80)
        isDead = true;
    if (player_x <= x)  //player left
        nx = -1;
    else if (player_x + 40 >= x + width)   //player right
        nx = 1;
    else nx = 0;

    if (player_y - 48 <= y - height)  //player under
        ny = -1;
    else if (player_y >= y)   //player above
        ny = 1;
    else ny = 0;

    vy = BOSS_SPELL_SPEED * dt*ny;
	vx = BOSS_SPELL_SPEED * dt * nx;

    CGameObject::Update(dt);

    if (leftSide && x > BOSS_MAP_WIDTH / 2)
        isDead = true;
    else if(!leftSide && x < BOSS_MAP_WIDTH / 2)
        isDead = true;

    if (state == BOSS_SPELL_STATE_DEAD && animations[ani]->currentFrame == 3)
        isDead = true;

    x += vx;
    y += vy;

}

void BossSpell::SetState(int state)
{
    CGameObject::SetState(state);
	switch (state)
	{
    case BOSS_SPELL_STATE_FLYING:
        break;
    case BOSS_SPELL_STATE_DEAD:
        vx = 0;
        vy = 0;
        break;
	}
}

void BossSpell::Render()
{
    if (state == BOSS_SPELL_STATE_FLYING)
        ani = BOSS_SPELL_ANI_FLYING;
    else
        ani = BOSS_SPELL_ANI_DEAD;
	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}