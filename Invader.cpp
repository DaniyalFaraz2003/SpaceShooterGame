#include "Invader.h"
#include <iostream>
using namespace std;

int Invader::bSize = 15;
int Invader::bulletInd = 0;
Bullet* Invader::bullets = new Bullet[bSize];

Invader::Invader() :Enemy(), animation(nullptr, Container(4, 1), 0.1f) {
	destroying = false;
	destroyT.loadFromFile("img/explosion(resized).png");
	animation.rectangle.width = this->destroyT.getSize().x / float(animation.getImageCount().x);
	animation.rectangle.height = this->destroyT.getSize().y / float(animation.getImageCount().y);

}

void Invader::updateDestroying(float dt)
{
	unsigned int row = 0;
	this->animation.update(row, dt, true);
	this->body.setTexture(this->destroyT);
	this->body.setTextureRect(animation.rectangle);
	if (this->animation.getCurrentImage().x == 3) {
		this->destroying = false;
		this->destroy();
		animation.reset();
	}
}
Invader::~Invader() {
}

void Invader::writeToFile(ofstream& file)
{
	file.write(reinterpret_cast<char*>(&show), sizeof(bool));
	file.write(reinterpret_cast<char*>(&fireInterval), sizeof(float));
	file.write(reinterpret_cast<char*>(&totalTime), sizeof(float));
	for (int i = 0; i < bSize; i++) {
		this->bullets[i].writeToFile(file);
	}
	file.write(reinterpret_cast<char*>(&destroying), sizeof(bool));
}

void Invader::readFromFile(ifstream& file)
{
	file.read(reinterpret_cast<char*>(&show), sizeof(bool));
	file.read(reinterpret_cast<char*>(&fireInterval), sizeof(float));
	file.read(reinterpret_cast<char*>(&totalTime), sizeof(float));
	for (int i = 0; i < this->bSize; i++) {
		this->bullets[i].readFromFile(file);
	}
	file.read(reinterpret_cast<char*>(&destroying), sizeof(bool));
}

void Invader::initBullets()
{
	for (int i = 0; i < bSize; i++) {
		bullets[i].setTexture("img/enemy_laser.png");
		bullets[i].setPosition(Container(-100.0f, -100.0f));
	}
}
