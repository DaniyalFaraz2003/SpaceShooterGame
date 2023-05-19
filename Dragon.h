#pragma once
#include "Enemy.h"
class Dragon :
    public Enemy
{
private:
    Texture beamT, figureT, leftCannonT, rightCannonT;
    RectangleShape figure, beamFigure, leftCannon, rightCannon;
    float firingTime;
    bool isFiring, leftIncoming, rightIncoming;
    bool rightGoing, leftGoing;
public:
    Dragon();
    bool come();
    bool go();
    void fire(float dt, float playerPos = 0);
    FloatRect getGlobalBounds();
    FloatRect getGlobalBounds_beam();
    void draw(RenderWindow& window);
};

