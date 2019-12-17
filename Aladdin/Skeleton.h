#ifndef SKELETON_H
#define SKELETON_H
#include "Enemy.h"
#include "Scene.h"

#define BBOX_WIDTH 51
#define BBOX_HEIGHT 88

#define SKELETON_START_RANGE_HORIZONTAL 200
#define SKELETON_START_RANGE_VERTICAL 10

enum SKELETON_STATE
{
    SKELETON_STATE_NOT_CREATE,
    SKELETON_STATE_CREATE = 101,
    SKELETON_STATE_DEAD = 5,
};

enum SKELETON_ANI
{
    SKELETON_ANI_CREATE,
    SKELETON_ANI_DEAD,
};
class Scene;
class Skeleton : public Enemy
{
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

	Scene* scene;
    bool exploded = false;
public:
    DWORD idle_start;
    Skeleton() : Enemy()
    {
        idle_start = 0;
        hitpoint = 2;
        scoreGain = 200;
        width = BBOX_WIDTH;
        height = BBOX_HEIGHT;
        lastFrameWidth = BBOX_WIDTH;
        lastFrameHeight = BBOX_HEIGHT;
        nx = 1;
    }

    virtual void SetState(int state);

	void Explode();
	void SetScene(Scene* s) { scene = s; }
};
#endif