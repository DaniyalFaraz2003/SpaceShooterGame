#pragma once
#include "AddOn.h"
class Danger :
    public AddOn
{
public:
    Danger(string path);
    string getType();
};

