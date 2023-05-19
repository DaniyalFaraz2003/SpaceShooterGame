#pragma once
#include "Invader.h"
class Alpha :
    public Invader
{
public:
    Alpha();
    string getType();
    void fire(float dt, float playerPos = 0);
};

