#ifndef MENUSCENE_H
#define MENUSCENE_H
#include "Scene.h"
#include "MovingObject.h"
#include "Map.h"
class MenuScene : public Scene
{
private:
    int choosing = 0; //sultan
    CMap *menuMap;
    MovingObject *blade_pointer;
public:
    MenuScene();
    void Update(DWORD);
    void Render();
    void Initialize();
};
#endif