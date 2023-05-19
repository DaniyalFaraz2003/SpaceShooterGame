#include "NumDisplay.h"

NumDisplay::NumDisplay(int n) {
	this->num = n;
	this->t0.loadFromFile("img/PNG/UI/numeral0.png");
	this->t1.loadFromFile("img/PNG/UI/numeral1.png");
	this->t2.loadFromFile("img/PNG/UI/numeral2.png");
	this->t3.loadFromFile("img/PNG/UI/numeral3.png");
	this->t4.loadFromFile("img/PNG/UI/numeral4.png");
	this->t5.loadFromFile("img/PNG/UI/numeral5.png");
	this->t6.loadFromFile("img/PNG/UI/numeral6.png");
	this->t7.loadFromFile("img/PNG/UI/numeral7.png");
	this->t8.loadFromFile("img/PNG/UI/numeral8.png");
	this->t9.loadFromFile("img/PNG/UI/numeral9.png");
	s0.setTexture(t0); s0.setScale(1.5, 1.5);
	s1.setTexture(t1); s1.setScale(1.5, 1.5);
	s2.setTexture(t2); s2.setScale(1.5, 1.5);
	s3.setTexture(t3); s3.setScale(1.5, 1.5);
	s4.setTexture(t4); s4.setScale(1.5, 1.5);
	s5.setTexture(t5); s5.setScale(1.5, 1.5);
	s6.setTexture(t6); s6.setScale(1.5, 1.5);
	s7.setTexture(t7); s7.setScale(1.5, 1.5);
	s8.setTexture(t8); s8.setScale(1.5, 1.5);
	s9.setTexture(t9); s9.setScale(1.5, 1.5);
}
void NumDisplay::add(int n) {
	this->num += n;
}

int NumDisplay::getNum() {
	return this->num;
}
void NumDisplay::setNum(int n) {
	this->num = n;
}
void NumDisplay::draw(RenderWindow& window, int posX, int posY) {
	int temp = this -> num;
	int digits = 0;

	while (temp > 0) {
		digits++;
		temp /= 10;
	}
	int offset = digits * 28.5;
	temp = this->num;
	if (this->num == 0) {
		s0.setPosition(25.0f, 0.0f);
		s0.move(posX, posY);
		window.draw(s0);
	}
	while (temp > 0) {
		int digit = temp % 10;
		temp /= 10;
		switch (digit) {
		case 0:
			s0.setPosition(offset, 0.0f);
			s0.move(posX, posY);
			window.draw(s0);
			break;
		case 1:
			s1.setPosition(offset, 0.0f);
			s1.move(posX, posY);
			window.draw(s1);
			break;
		case 2:
			s2.setPosition(offset, 0.0f);
			s2.move(posX, posY);
			window.draw(s2);
			break;
		case 3:
			s3.setPosition(offset, 0.0f);
			s3.move(posX, posY);
			window.draw(s3);
			break;
		case 4:
			s4.setPosition(offset, 0.0f);
			s4.move(posX, posY);
			window.draw(s4);
			break;
		case 5:
			s5.setPosition(offset, 0.0f);
			s5.move(posX, posY);
			window.draw(s5);
			break;
		case 6:
			s6.setPosition(offset, 0.0f);
			s6.move(posX, posY);
			window.draw(s6);
			break;
		case 7:
			s7.setPosition(offset, 0.0f);
			s7.move(posX, posY);
			window.draw(s7);
			break;
		case 8:
			s8.setPosition(offset, 0.0f);
			s8.move(posX, posY);
			window.draw(s8);
			break;
		case 9:
			s9.setPosition(offset, 0.0f);
			s9.move(posX, posY);
			window.draw(s9);
			break;
		}
		offset -= 28.5;
	}
}