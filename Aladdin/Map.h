#ifndef CMAP_H
#define CMAP_H
#include "GameObject.h"
#include "define.h"


class CMap : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
}; 
#endif