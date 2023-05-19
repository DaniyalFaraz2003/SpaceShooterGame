#pragma once
#include "Enemy.h"
class Monster :
    public Enemy
{
private:
    bool moveLeft, moveRight;
    Texture beamT, monsterT;
    Sprite beam;
    RectangleShape figure, beamFigure;
    float firingTime;
    bool isFiring;
public:
    Monster();
    bool come();
    void move(float x, float y);
    bool go();
    void fire(float dt, float playerPos = 0);
    FloatRect getGlobalBounds();
    FloatRect getGlobalBounds_beam();
    void draw(RenderWindow& window);
};

