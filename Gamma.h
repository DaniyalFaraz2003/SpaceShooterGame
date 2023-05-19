#pragma once
#include "Invader.h"
class Gamma :
    public Invader
{
public:
    Gamma();
    string getType();
    void fire(float dt, float playerPos = 0);
};

