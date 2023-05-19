#include "Monster.h"

Monster::Monster() {
	this->monsterT.loadFromFile("img/monster1(resized).png");
	this->beamT.loadFromFile("img/laser.png");
	this->beamFigure.setTexture(&beamT);
	this->figure.setTexture(&monsterT);
	this->figure.setSize(Vector2f(300, 300));
	this->figure.setFillColor(Color::White);
	this->beamFigure.setSize(Vector2f(30, 600));
	this->beamFigure.setFillColor(Color::White);
	this->figure.setPosition(100, -300);
	this->beamFigure.setPosition(this -> figure.getPosition().x + this -> figure.getGlobalBounds().width / 2, 
		this -> figure.getPosition().y + this -> figure.getGlobalBounds().height);
	this->firingTime = 0; this->setFireInterval(0);
	this->moveRight = true; this->moveLeft = false;
	this->isFiring = false;
}

bool Monster::come() {
	if (this->figure.getPosition().y < 50) {
		this->figure.move(0.0, 0.2f); return false;
	}
	return true;
}

void Monster::move(float x, float y)
{
	if (moveRight) {
		this->figure.move(x, y);
		if (this->figure.getPosition().x >= 550) {
			this->moveRight = false;
			this->moveLeft = true;
		}
	}
	else if (moveLeft) {
		this->figure.move(-x, y);
		if (this->figure.getPosition().x < -100) {
			this->moveRight = true;
			this->moveLeft = false;
		}
	}
}

bool Monster::go() {
	if (this->figure.getPosition().y > -300) {
		this->figure.move(0.0, -0.2f); return false;
	}
	return true;
}

void Monster::fire(float dt, float playerPos) {
	if (!this -> isFiring) {
		this->setFireInterval(this->getFireInterval() + dt);
		this->beamFigure.setPosition(-200, -100);
		if (this->getFireInterval() > 5.0) {
			this->isFiring = true;
			this->setFireInterval(0);
		}
	}
	else {
		this->firingTime += dt;
		this->beamFigure.setPosition(this->figure.getPosition().x + this->figure.getGlobalBounds().width / 2 - 15,
			this->figure.getPosition().y + this->figure.getGlobalBounds().height - 70);
		if (this->firingTime >= 7.0) {
			this->isFiring = false;
			this->firingTime = 0;
		}
	}
	
}

FloatRect Monster::getGlobalBounds()
{
	return this -> figure.getGlobalBounds();
}

FloatRect Monster::getGlobalBounds_beam()
{
	return this -> beamFigure.getGlobalBounds();
}

void Monster::draw(RenderWindow& window) {
	if (this->isFiring) {
		window.draw(this->beamFigure);
		window.draw(this->figure);
	}
	else window.draw(this->figure);
}