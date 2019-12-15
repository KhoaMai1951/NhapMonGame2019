#ifndef BAT_H
#define BAT_H

#include "Enemy.h"

#define BBOX_WIDTH 20   //when flying
#define BBOX_HEIGHT 16
#define START_ATTACK_RANGE 100
#define MOVE_SPEED 0.006f
#define IDLE_TIME 3000
#define ATTACK_TIME 5000

enum BAT_STATE
{
	BAT_STATE_IDLE = 101,
	BAT_STATE_FLYING = 102,
	BAT_STATE_DEAD = 5,
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
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
    float idle_x, idle_y;
public:
    DWORD idle_start, flying_start;
    bool is_hit = false;
	Bat() : Enemy()
	{
        flying_start = 0;
		idle_start = 0;
		hitpoint = 1;
		score = 200;
		width = BBOX_WIDTH;
		height = BBOX_HEIGHT;
		lastFrameWidth = BBOX_WIDTH;
		lastFrameHeight = BBOX_HEIGHT;
		nx = 1;
	}
    void SetIdlePositon(float _x, float _y) { idle_x = _x; idle_y = _y; }
	virtual void SetState(int state);
};
#endif 