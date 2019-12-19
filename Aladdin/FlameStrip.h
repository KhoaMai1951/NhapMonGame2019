#ifndef FLAMESTRIP_H
#define FLAMESTRIP_H
#include "GameObject.h"
#include "debug.h"
#include "SpatialGrid.h"

#define FIRESTRIP_WAITING_TIME 1000

enum FLAMESTRIP_STATE
{
	FLAMESTRIP_STATE_DO_DAMAGE,
	FLAMESTRIP_STATE_NOT_DO_DAMAGE,
};

enum FLAMESTRIP_ANI
{
	FLAMESTRIP_ANI_DO_DAMAGE,
	FLAMESTRIP_ANI_NOT_DO_DAMAGE,
};

enum FLAMESTRIP_SIZE
{
    FLAMESTRIP_WIDTH = 31,
    FLAMESTRIP_HEIGHT = 56,
};

class FlameStrip : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

    DWORD start_time, burn_time = 0;
public:
	bool do_damage;
	FlameStrip() : CGameObject()
	{
		start_time = 0;
		//ani = 0;
		//width = FLAMESTRIP_WIDTH;
		//height = FLAMESTRIP_HEIGHT;
	}

	virtual void SetState(int state);
	void InsertToGrid() { SpatialGrid::GetInstance()->Insert(this); }
};
#endif