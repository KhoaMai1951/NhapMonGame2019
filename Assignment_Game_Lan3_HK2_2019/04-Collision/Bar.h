#pragma once
#include "GameObject.h"

#define BAR_MOVE_SPEED		0.3f 

#define BAR_MOVE_DOWN 500
#define BAR_MOVE_UP 600
#define BAR_IDLE 700

#define BAR_BBOX_WIDTH 10
#define BAR_BBOX_HEIGHT 40

#define MARIO_UNTOUCHABLE_TIME 5000


class CBar : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
public:
	CBar() : CGameObject()
	{
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
    void Move(float _y);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};