#pragma once
#include "Invader.h"
class Beta :
    public Invader
{
public:
    Beta();
    string getType();
    void fire(float dt, float playerPos = 0);
};

