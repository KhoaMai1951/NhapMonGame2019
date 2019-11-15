#pragma once
#include "GameObject.h"

class Enemy : public CGameObject
{  
public:
    int hitpoint;
    int score;

    Enemy();
    ~Enemy();
};