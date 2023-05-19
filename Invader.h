#pragma once
#include <iostream>
using namespace std;
#include "Enemy.h"
class Invader :
    public Enemy
{
public:
    Texture destroyT;
    Animation animation;
    //int bulletInd;
    static int bulletInd;
    float totalTime = 0;
    //Bullet* bullets;
    static Bullet* bullets;
    static int bSize;
    //int bSize = 4;
private:
    bool destroying;
    FloatRect getGlobalBounds_beam() { return FloatRect(); }
    bool come() { return 0; }
    bool go() { return 0; }
public:
    virtual void fire(float dt, float playerPos = 0) = 0;
    Invader();
    void updateDestroying(float dt);
    virtual string getType() = 0;
    ~Invader();
    void writeToFile(ofstream& file);
    void readFromFile(ifstream& file);
    static void initBullets();
    bool getDestroying() { return this->destroying; }
    void setDestroying(bool val) { this->destroying = val; }
};

