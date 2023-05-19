#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Bullet.h"
#include "AddOn.h"
#include "PowerUp.h"
#include "Fire.h"
#include "Enemy.h"
#include "NumDisplay.h"
#include<string.h>
using namespace sf;
class Player {
private:
	const int WIDTH = 750;
	const int HEIGHT = 660;
	Animation animation;
	Texture destroyT;
	unsigned int row = 0;
	int number;
	static int lives;
public:
	//vars used for animation
	bool destroying;
public:
	NumDisplay score;
	Texture leftT, fireT, fireLT, fireRT, powerT, powerLT, powerRT; Sprite left;
	Texture rightT, op2, op2R, op2L, op3, op3R, op3L; Sprite right;
	string mov_dir;
	int bulletInd;
	const int bSize = 7;
	Bullet* bullets10, * bullets_10, * bullets20, * bullets_20, * bullets30, * bullets_30;
	Bullet* bullets;
	Texture tex;
	Sprite sprite, fireS;
	float speed = 0.1, speedY = 0, speedX = 0;
	int x, y;
	AddOn* addOn;
	float addOnDuration = 0.0;
	bool isPowered, fireBullets;
	float topSpeed;
	float acc = 0.0001;
public:
	void useAddOn(float time, AddOn* addOn);
	bool intersects(FloatRect r1, FloatRect r2);
	void updateDestroying(float dt);
	void destroy();
	bool collides(const Bullet& other);
	bool collides(Enemy& e);
	bool collides(AddOn* other);
	Player(std::string png_path);
	~Player();
	void fire();
	static void setLives(int n);
	static int getLives(); static void addLife() { Player::lives++; }
	static void subLife() { Player::lives--; }
	FloatRect getGlobalBounds() const;
	Container move(std::string s);
	void setTextureRect(int w, int x, int y, int z);
	void setTextureRect(FloatRect f);
	Container getPosition();
	void writeToFile(ofstream& file);
	void readFromFile(ifstream& file);
	void setSpaceShip();
	void setNumber(int num) { this->number = num; }
};

