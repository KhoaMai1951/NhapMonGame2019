#ifndef COMPLETE_ALADDIN_H
#define COMPLETE_ALADDIN_H
#include "GameObject.h"

class MovingObject : public CGameObject
{
public:
    MovingObject() :CGameObject()
    {

    }
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif