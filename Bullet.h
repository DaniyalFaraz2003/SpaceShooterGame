#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
using namespace std;
using namespace sf;

struct Container {
	float x, y;
	Container(float x = 0, float y = 0) :x(x), y(y) {}
	bool operator==(const Container& c) {
		return this->x == c.x && this->y == c.y;
	}
	bool operator>=(const Container& c) {
		return *this == c || (this -> x > c.x && this -> y > c.y);
	}
};

class Bullet
{
private:
	Texture straightT, leftT, rightT, stf, rtf, ltf;
	Sprite body, left, right, straight, sf, rf, lf;
	Container position;
	bool show;
public:
	string move_dir;
	Bullet(string path = "");
	void setTexture(string path);
	void setSprite(string dir, bool isFire);
	Container getPosition();
	void setPosition(Container pos);
	void destroy();
	void setShow();
	void move(float xFactor, float yFactor);
	void hasCollided();
	FloatRect getGlobalBounds() const;
	bool isOutOfGame();
	void draw(RenderWindow& window);
	void writeToFile(ostream& file);
	void readFromFile(istream& file);
};

