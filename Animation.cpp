#include "Animation.h"

Animation::Animation(Texture* texture, Container imageCount, float switchTime) {
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;
    if (texture != nullptr) {
        rectangle.width = texture->getSize().x / float(imageCount.x);
        rectangle.height = texture->getSize().y / float(imageCount.y);
    }
}
void Animation::reset() {
    currentImage.x = 0;
    totalTime = 0.0f;
}
void Animation::update(unsigned int& row, float deltaTime, bool faceRight) {
    currentImage.y = row;
    totalTime += deltaTime;
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x += 1;
        if (currentImage.x >= imageCount.x) {
            currentImage.x = 0;
            row++;
            if (row >= imageCount.y) row = 0;
        }
    } 
    rectangle.top = currentImage.y * rectangle.height;
    if (faceRight) {
        rectangle.left = currentImage.x * rectangle.width;
        rectangle.width = abs(rectangle.width);
    }
    else {
        rectangle.left = (currentImage.x + 1) * abs(rectangle.width);
        rectangle.width = -abs(rectangle.width);
    }
}