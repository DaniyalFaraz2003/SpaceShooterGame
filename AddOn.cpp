#include "AddOn.h"

AddOn::AddOn(string path) {
	this->fallTime = 0.0;
	this->t.loadFromFile(path);
	this->body.setTexture(this->t);
}
void AddOn::fall() {

	this->body.move(0.0f, 0.1f);
}

void AddOn::spawn()
{
	this->body.setPosition(float(30 + rand() % 720), -100.0f);
}

void AddOn::draw(RenderWindow& window)
{
	window.draw(this->body);
}
