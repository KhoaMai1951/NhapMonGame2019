#ifndef GROUND_H
#define GROUND_H
#include "GameObject.h"

class Ground : public CGameObject
{
public:
    int type;
    virtual void Render();
    virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
#endif