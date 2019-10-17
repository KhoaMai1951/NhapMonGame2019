#pragma once
#include "GameObject.h"

#define BALL_MOVE_SPEED		0.6f 

#define BALL_BBOX_WIDTH 10
#define BALL_BBOX_HEIGHT 40

#define BALL_IDLE 777
#define BALL_MOVING 888

#define MARIO_UNTOUCHABLE_TIME 5000


class CBall : public CGameObject
{

	int level;
	int untouchable;
	DWORD untouchable_start;
public:
	CBall() : CGameObject()
	{
        vx = 0;
        vy = 0;
        state = BALL_IDLE;
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
    float Random(int min, int max);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};