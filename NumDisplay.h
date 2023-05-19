#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class NumDisplay
{
private:
	Texture t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;
	Sprite s0, s1, s2, s3, s4, s5, s6, s7, s8, s9;
	int num;
public:
	int getNum();
	void setNum(int n);
	void add(int n);
	NumDisplay(int n = 0);
	void draw(RenderWindow& window, int posX, int posY);
};

