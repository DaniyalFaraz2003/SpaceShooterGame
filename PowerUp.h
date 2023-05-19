#pragma once
#include "AddOn.h"
class PowerUp :
    public AddOn
{
public:
    PowerUp(string path);
    string getType();
};

