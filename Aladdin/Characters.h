#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "GameObject.h"

#define BBOX_WIDTH 16
#define BBOX_HEIGHT 16

enum CHARACTERS_STATE
{
};

enum CHARACTERS_ANI
{
};

class Characters : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);


public:
	Characters() : CGameObject()
	{
		//lastFrameWidth = APPLE_IDLE_WIDTH;
		//lastFrameHeight = APPLE_IDLE_HEIGHT;
		width = BBOX_WIDTH;
		height = BBOX_HEIGHT;
	}
	virtual void SetState(int state);
	virtual void Render();
};
#endif
