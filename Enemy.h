#pragma once
#include <string>
#include "Bullet.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Enemy
{
private:
	Texture t;
	Container position;
protected:
	bool show;
	float fireInterval;
public:
	Sprite body;
	float getFireInterval();
	void setFireInterval(float val);
	bool intersects(FloatRect r1, FloatRect r2);
	Enemy();
	virtual void draw(RenderWindow& window);
	void setTexture(string path);
	Container getPos();
	void setPos(Container pos);
	Texture& getTexture();
	virtual void move(float Xfactor, float Yfactor);
	bool getShow();
	void setShow(bool trueOrFalse);
	void reSize(Container size);
	void destroy();
	virtual void fire(float dt, float playerPos = 0) = 0;
	virtual bool come() = 0;
	virtual bool go() = 0;
	bool collides(const Bullet& other);
	FloatRect getLocalBounds();
	virtual FloatRect getGlobalBounds();
	virtual FloatRect getGlobalBounds_beam() = 0;
};

