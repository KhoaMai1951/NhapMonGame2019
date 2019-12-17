#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"

class Enemy : public CGameObject
{  
public:
    float attack_size = 0;
    bool start_attack = false;
    DWORD attack_start = 0;
    int hitpoint;

    Enemy();
    ~Enemy();
};
#endif