#ifndef HUD_H
#define HUD_H
#include "GameObject.h"

class HUD : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);


public:
	HUD() : CGameObject()
	{
		ani = 0;
	}
	virtual void SetState(int state);
	virtual void Render();
};
#endif
