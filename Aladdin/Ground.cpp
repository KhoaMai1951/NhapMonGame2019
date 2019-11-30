#include "Ground.h"

void Ground::Render()
{
    animations[0]->Render(x, y);
    if(name == "Ground0" || name == "Ground1" || name == "Ground3")
        RenderBoundingBox();
}

void Ground::GetBoundingBox(float &l, float &t, float &r, float &b)
{
    l = x;
    t = y;
    r = x + width;
    b = y - height;
}