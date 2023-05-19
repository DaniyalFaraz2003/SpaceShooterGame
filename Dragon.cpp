#include "Dragon.h"

Dragon::Dragon() {
	this->beamT.loadFromFile("img/bossBeam.png");
	this->figureT.loadFromFile("img/Boss.png");
	this->beamFigure.setTexture(&beamT);
	this->rightCannonT.loadFromFile("img/cannon(right).png");
	this->leftCannonT.loadFromFile("img/cannon(left).png");
	this->rightCannon.setTexture(&rightCannonT); this->leftCannon.setTexture(&leftCannonT);
	this->figure.setTexture(&figureT);
	this->figure.setSize(Vector2f(300, 300));
	this->figure.setFillColor(Color::White);
	this->beamFigure.setSize(Vector2f(750, 30));
	this->beamFigure.setFillColor(Color::White);
	this->figure.setPosition(230, -300);
	this->rightCannon.setSize(Vector2f(200, 80));
	this->rightCannon.setFillColor(Color::White);
	this->leftCannon.setSize(Vector2f(200, 80));
	this->leftCannon.setFillColor(Color::White);
	this->rightCannon.setPosition(-500, -500);
	this->leftCannon.setPosition(-500, -500);
	this->firingTime = 0; this->setFireInterval(0);
	this->rightIncoming = true; this->leftIncoming = false;
	rightGoing = false, leftGoing = false;
	this->isFiring = false;
}

bool Dragon::come() {
	if (this->figure.getPosition().y < 50) {
		this->figure.move(0.0, 0.2f); return false;
	}
	return true;
}



bool Dragon::go() {
	if (this->figure.getPosition().y > -300) {
		this->figure.move(0.0, -0.2f); return false;
	}
	return true;
}

void Dragon::fire(float dt, float playerPos) {
	if (!this->isFiring) {
		this->setFireInterval(this->getFireInterval() + dt);
		this->beamFigure.setPosition(-200, -100);
		if (leftGoing) {
			leftCannon.move(-0.05f, 0.0f);
			if (leftCannon.getPosition().x < -200) leftGoing = false;
		}
		if (rightGoing) {
			rightCannon.move(0.05f, 0.0f);
			if (rightCannon.getPosition().x > 750) rightGoing = false;
		}
		if (this->getFireInterval() > 1.4) {
			this->isFiring = true;
			this->setFireInterval(0);
			rightCannon.setPosition(750, playerPos); leftCannon.setPosition(-200, playerPos);
		}
	}
	else {
		if (rightIncoming) {
			rightCannon.move(-0.02, 0.0f);
			if (rightCannon.getPosition().x <= 650) {
				rightCannon.move(0.02, 0.0f);
				this->firingTime += dt;
				this->beamFigure.setPosition(rightCannon.getPosition().x - 700, rightCannon.getPosition().y + 10);
				if (this->firingTime >= 3.0) {
					rightIncoming = false;
					rightGoing = true;
					leftIncoming = true;
					leftGoing = false;
					this->isFiring = false;
					this->firingTime = 0;
				}
			}
		}
		else if (leftIncoming) {
			leftCannon.move(0.02, 0.0f);
			if (leftCannon.getPosition().x >= -100) {
				leftCannon.move(-0.02, 0.0f);
				this->firingTime += dt;
				this->beamFigure.setPosition(leftCannon.getPosition().x + 160, rightCannon.getPosition().y + 10);
				if (this->firingTime >= 3.0) {
					rightIncoming = true;
					rightGoing = false;
					leftIncoming = false;
					leftGoing = true;
					this->isFiring = false;
					this->firingTime = 0;
				}
			}
		}
	}
}

FloatRect Dragon::getGlobalBounds()
{
	return this->figure.getGlobalBounds();
}

FloatRect Dragon::getGlobalBounds_beam()
{
	return this->beamFigure.getGlobalBounds();
}

void Dragon::draw(RenderWindow& window) {
	if (this->isFiring) {
		window.draw(this->figure);
		window.draw(this->beamFigure);
	}
	else window.draw(this->figure);
	window.draw(this->rightCannon);
	window.draw(this->leftCannon);
}