#pragma once
#include "Enemy.h"

#define WALKING_SPEED 0.05f;

#define BBOX_WIDTH 44
#define BBOX_HEIGHT 58

enum GUARD0_STATE
{
	STATE_IDLE = 101,
	STATE_WALK = 102,
	STATE_ATTACK = 103,
	STATE_HURT = 104,
	STATE_DEAD = 105,
};

enum GUARD0_ANI
{
	ANI_IDLE_RIGHT,
	ANI_IDLE_LEFT,

	ANI_WALK_RIGHT,
	ANI_WALK_LEFT,

	ANI_ATTACK_RIGHT,
	ANI_ATTACK_LEFT,

	ANI_HURT_RIGHT,
	ANI_HURT_LEFT,
	ANI_DEAD,

};

class Guard0 : public Enemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Guard0() : Enemy()
	{
		hitpoint = 2;
		score = 200;
		width = BBOX_WIDTH;
		height = BBOX_HEIGHT;
		SetState(STATE_IDLE);
		lastFrameWidth = BBOX_WIDTH;
		lastFrameHeight = BBOX_HEIGHT;
		nx = 1;
	}
	virtual void SetState(int state);
};