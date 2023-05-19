#include "Gamma.h"

Gamma::Gamma() :Invader() {
	this->setTexture("img/gamma.png");
	this->setFireInterval(1.0);
}

string Gamma::getType()
{
	return "gamma";
}

void Gamma::fire(float dt, float playerPos) {
	totalTime += dt;
	if (totalTime >= this->getFireInterval()) {
		totalTime = -1;
		bullets[bulletInd].setPosition(Container(this->body.getPosition().x + (this->body.getLocalBounds().width / 2) - 20,
			this->body.getPosition().y - 30 + (this->body.getLocalBounds().height / 2)));
		bullets[bulletInd].setShow();
		bulletInd += 1;
		if (bulletInd == bSize) bulletInd = 0;
	}
}