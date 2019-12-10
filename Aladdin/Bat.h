#pragma once
#include "Enemy.h"

#define BBOX_WIDTH 20   //when flying
#define BBOX_HEIGHT 16

enum BAT_STATE
{
	BAT_STATE_IDLE = 101,
	BAT_STATE_FLYING = 102,
	BAT_STATE_DEAD = 103,
};

enum BAT_ANI
{
	BAT_ANI_IDLE,
	BAT_ANI_FLYING,
	BAT_ANI_DEAD,
};

class Bat : public Enemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	DWORD idle_start;
	Bat() : Enemy()
	{
		idle_start = 0;
		hitpoint = 2;
		score = 200;
		width = BBOX_WIDTH;
		height = BBOX_HEIGHT;
		lastFrameWidth = BBOX_WIDTH;
		lastFrameHeight = BBOX_HEIGHT;
		nx = 1;
	}

	virtual void SetState(int state);
};