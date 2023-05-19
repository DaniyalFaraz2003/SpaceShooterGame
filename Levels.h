#pragma once
#include "Invader.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Levels
{
public:
	int wave;
	int levelNumber;
	Levels();
	void initEnemies(Invader*** enemies);
	void rectangle(Invader*** enemies);
	void circle(Invader*** enemies);
	void diamond(Invader*** enemies);
	void triangle(Invader*** enemies);
	void cross(Invader*** enemies);
	void filled(string shape, Invader*** enemies);
};

