#include "Enemy.h"
#include <iostream>
using namespace std;
Enemy::Enemy() {
	this->show = false;
}


void Enemy::draw(RenderWindow& window)
{
	if (show) window.draw(this->body);
}

void Enemy::setTexture(string path)
{
	t.loadFromFile(path);
	body.setTexture(t);
}

void Enemy::setPos(Container pos) {
	this->body.setPosition(pos.x, pos.y);
}


void Enemy::move(float Xfactor, float Yfactor)
{
	if (show) this->body.move(Xfactor, Yfactor);
}

Texture& Enemy::getTexture()
{
	return this->t;
}

bool Enemy::getShow()
{
	return this->show;
}

void Enemy::setShow(bool trueOrFalse)
{
	this->show = trueOrFalse;
}

void Enemy::destroy()
{
	this->setPos(Container(-200.0f, -100.0f));
	this->show = false;
}

float Enemy::getFireInterval()
{
	return this->fireInterval;
}
void Enemy::setFireInterval(float val)
{
	this->fireInterval = val;
}

bool Enemy::collides(const Bullet& other)
{
	//if (this->body.getGlobalBounds().intersects(other.getGlobalBounds())) return true;
	return intersects(body.getGlobalBounds(), other.getGlobalBounds());
}


bool Enemy::intersects(FloatRect r1, FloatRect r2) {
	float x1 = r1.left + r1.width / 2;
	float y1 = r1.top + r1.height / 2;

	float x2 = r2.left + r2.width / 2;
	float y2 = r2.top + r2.height / 2;

	return (abs(x1 - x2) < (r1.width / 2 + r2.width / 2)) && (abs(y1 - y2) < (r1.height / 2 + r2.height / 2));
}


FloatRect Enemy::getLocalBounds()
{
	return this -> body.getLocalBounds();
}

FloatRect Enemy::getGlobalBounds()
{
	return this -> body.getGlobalBounds();
}

void Enemy::reSize(Container size) {
	this->body.setScale(size.x / this->body.getLocalBounds().width,
		size.y / this->body.getLocalBounds().height);
}

Container Enemy::getPos() {
	return Container(this -> body.getPosition().x, this -> body.getPosition().y);
}