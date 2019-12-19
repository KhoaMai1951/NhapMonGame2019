#ifndef FLAMESTRIP_H
#define FLAMESTRIP_H
#include "GameObject.h"
#include "debug.h"
#include "SpatialGrid.h"

#define BBOX_WIDTH 31
#define BBOX_HEIGHT 56
#define FIRESTRIP_WAITING_TIME 1000

enum FLAMESTRIP_STATE
{
	FLAMESTRIP_STATE_DO_DAMAGE,
	FLAMESTRIP_STATE_NOT_DO_DAMAGE,
};

enum FLAMSTRIP_ANI
{
	FLAMESTRIP_ANI_DO_DAMAGE,
	FLAMESTRIP_ANI_NOT_DO_DAMAGE,
};

class FlameStrip : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	DWORD start_time;
public:
	bool do_damage;
	FlameStrip() : CGameObject()
	{
		start_time = 0;
		//ani = 0;
		width = BBOX_WIDTH;
		height = BBOX_HEIGHT;
	}

	virtual void SetState(int state);
	void InsertToGrid() { SpatialGrid::GetInstance()->Insert(this); }
};
#endif