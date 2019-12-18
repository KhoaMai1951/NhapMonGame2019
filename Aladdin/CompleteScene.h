#ifndef COMPLETESCENE_H
#define COMPLETESCENE_H
#include "Scene.h"
#include "MovingObject.h"
#include "Map.h"
class CompleteScene : public Scene
{
private:
    MovingObject *completeAladdin, *completeAbu;
    CMap *completeMap;
public:
    CompleteScene();
    void Update(DWORD);
    void Render();
    void Initialize();
};
#endif