#ifndef BOSS_SPELL_H
#define BOSS_SPELL_H

#include "set"
#include "SpatialGrid.h"
#include "Enemy.h"
#include "Ground.h"
#include "debug.h"


#define BOSS_SPELL_SPEED 0.5f
#define BBOX_WIDTH 30
#define BBOX_HEIGHT 23

enum BossSpellState
{
    BOSS_SPELL_STATE_FLYING,
    BOSS_SPELL_STATE_DEAD = 5,
};
enum BossSpellAni
{
    BOSS_SPELL_ANI_FLYING,
    BOSS_SPELL_ANI_DEAD
};

class BossSpell : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
    float player_x, player_y;
public:
	BossSpell() : CGameObject()
	{
		vx = 0;
		vy = 0;
		width = BBOX_WIDTH;
		height = BBOX_HEIGHT;
	}
    bool leftSide;
    void setPlayerPosition(float _x, float _y) { player_x = _x; player_y = _y; }
	virtual void SetState(int state);
	void InsertToGrid() { SpatialGrid::GetInstance()->Insert(this); }
};

#endif // ! BONE_H