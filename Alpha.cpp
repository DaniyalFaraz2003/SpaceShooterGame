#include "Alpha.h"

Alpha::Alpha() :Invader() {
	this->setTexture("img/alpha.png");
	this->setFireInterval(3.0);
}

string Alpha::getType()
{
	return "alpha";
}

void Alpha::fire(float dt, float playerPos) {
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