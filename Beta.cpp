#include "Beta.h"

Beta::Beta() :Invader() {
	//this->setTexture("img/enemy_3(resized).png");
	this->setTexture("img/beta.png");
	this->setFireInterval(2.0);
}

string Beta::getType()
{
	return "beta";
}

void Beta::fire(float dt, float playerPos) {
	totalTime += dt;
	if (totalTime >= this->getFireInterval()) {
		totalTime = 0;
		bullets[bulletInd].setPosition(Container(this->body.getPosition().x + (this->body.getLocalBounds().width / 2) - 20,
			this->body.getPosition().y - 30 + (this->body.getLocalBounds().height / 2)));
		bullets[bulletInd].setShow();
		bulletInd += 1;
		if (bulletInd == bSize) bulletInd = 0;
	}
}