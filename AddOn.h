#pragma once

#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class AddOn
{
private:
	Sprite body;
	Texture t;
public:
	float fallTime;
	AddOn(string path);
	virtual string getType() = 0;
	void fall();
	Sprite& getBody() { return this->body; }
	void spawn();
	void draw(RenderWindow& window);
};

