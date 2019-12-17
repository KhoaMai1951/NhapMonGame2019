#ifndef FACE_H
#define FACE_H
#include "GameObject.h"

#define BBOX_WIDTH 17
#define BBOX_HEIGHT 16

enum FACE_STATE
{

};

enum FACE_ANI
{
	FACE_ANI_1,
};

class Face : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);


public:
	Face() : CGameObject()
	{
		ani = FACE_ANI_1;
		//lastFrameWidth = APPLE_IDLE_WIDTH;
		//lastFrameHeight = APPLE_IDLE_HEIGHT;
		width = BBOX_WIDTH;
		height = BBOX_HEIGHT;
	}
	virtual void SetState(int state);
	virtual void Render();
};
#endif
