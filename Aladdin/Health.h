#ifndef HEALTH_H
#define HEALTH_H
#include "GameObject.h"

#define BBOX_WIDTH 119
#define BBOX_HEIGHT 32

enum HEALTH_STATE
{

};

enum HEALTH_ANI
{
	HEALTH_ANI_1,
	HEALTH_ANI_2,
	HEALTH_ANI_3,
	HEALTH_ANI_4,
	HEALTH_ANI_5,
	HEALTH_ANI_6,
	HEALTH_ANI_7,
	HEALTH_ANI_8,
	HEALTH_ANI_9,
};

class Health : public CGameObject
{


public:
	float HealthRatio = 1; // health ratio = aladdin health at the moment / aladdin max health

	Health() : CGameObject()
	{
		//lastFrameWidth = APPLE_IDLE_WIDTH;
		//lastFrameHeight = APPLE_IDLE_HEIGHT;
		width = BBOX_WIDTH;
		height = BBOX_HEIGHT;
	}
	LPGAMEOBJECT InitHealth() {
		Health* health = new Health();
		health->AddAnimation(600);
		health->AddAnimation(601);
		health->AddAnimation(602);
		health->AddAnimation(603);
		health->AddAnimation(604);
		health->AddAnimation(605);
		health->AddAnimation(606);
		health->AddAnimation(607);
		health->AddAnimation(608);
	}
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
#endif
