#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"

class Enemy : public CGameObject
{  
public:
    int hitpoint;
    int score;

    Enemy();
    ~Enemy();
};
#endif