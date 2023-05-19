#pragma once
#include "Bullet.h"
#include <SFML/Graphics.hpp>
using namespace sf;



class Animation {
public:
    Animation(Texture* texture, Container imageCount, float switchTime);
    ~Animation() {}
    void update(unsigned int& row, float deltaTime, bool faceRight);
    Container getCurrentImage() { return this->currentImage; }
    Container getImageCount() { return this->imageCount; }
    void reset();
public:
    IntRect rectangle;
private:
    Container imageCount;
    Container currentImage;
    float totalTime;
    float switchTime;
};

