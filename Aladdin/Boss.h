#ifndef BOSS_H
#define BOSS_H
#include "Enemy.h"
#include "Scene.h"

#define WALKING_SPEED 0.05f;

#define BBOX_WIDTH 60	//87
#define BBOX_HEIGHT 73
#define BBOX_WIDTH2 81	//11
#define BOSS_MAX_HITPOINT 12

enum BOSS_STATE
{
	BOSS_STATE_ATTACK,
	BOSS_STATE_ATTACK2,
	BOSS_STATE_HURT,
};

enum BOSS_ANI
{
	BOSS_ANI_ATTACK1_RIGHT,
	BOSS_ANI_ATTACK1_LEFT,
	BOSS_ANI_ATTACK2_RIGHT,
	BOSS_ANI_ATTACK2_LEFT,
};
class Scene;
class Boss : public Enemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

public:
	Scene* scene;
	DWORD idle_start;
	bool isHumanForm = true, attacking = false;
	Boss() : Enemy()
	{
		idle_start = GetTickCount();
		hitpoint = BOSS_MAX_HITPOINT;
		scoreGain = 100;
		width = BBOX_WIDTH;
		height = BBOX_HEIGHT;
		lastFrameWidth = BBOX_WIDTH;
		lastFrameHeight = BBOX_HEIGHT;
		nx = -1;
	}
	virtual void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void SetScene(Scene* s) { scene = s; }
	void ChangeForm() {
		if (isHumanForm)
			isHumanForm = false;
		else
			isHumanForm = true;
	}
};
#endif