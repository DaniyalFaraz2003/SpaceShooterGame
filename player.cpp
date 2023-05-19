#include "player.h"
#include <iostream>

int Player::lives = 3;

Player::Player(std::string png_path):animation(nullptr, Container(9, 9), 0.01f) {
	isPowered = false; fireBullets = false;
	this->addOn = nullptr;
	bulletInd = 0;
	destroying = false;
	op2.loadFromFile("img/option2.png"); op2R.loadFromFile("img/option2(right).png"); op2L.loadFromFile("img/option2(left).png"); 
	op3.loadFromFile("img/option3.png"); op3R.loadFromFile("img/option3(right).png"); op3L.loadFromFile("img/option3(left).png");
	destroyT.loadFromFile("img/exp.png");
	leftT.loadFromFile("img/mship1(left).png"); rightT.loadFromFile("img/mship1(right).png");
	animation.rectangle.width = this->destroyT.getSize().x / float(animation.getImageCount().x);
	animation.rectangle.height = this->destroyT.getSize().y / float(animation.getImageCount().y);
	bullets10 = new Bullet[this->bSize]; bullets_10 = new Bullet[this->bSize];
	bullets20 = new Bullet[this->bSize]; bullets_20 = new Bullet[this->bSize];
	bullets30 = new Bullet[this->bSize]; bullets_30 = new Bullet[this->bSize];
	this->bullets = new Bullet[this->bSize];
	for (int i = 0; i < this->bSize; i++) {
		this->bullets[i].setTexture("img/PNG/Lasers/laserBlue01.png");
		this->bullets[i].setPosition(Container(-100.0f, -100.0f));
		bullets10[i].setTexture("img/PNG/Lasers/laser10.png"); bullets_10[i].setTexture("img/PNG/Lasers/laser_10.png");
		bullets10[i].setPosition(Container(-100.0f, -100.0f)); bullets_10[i].setPosition(Container(-100.0f, -100.0f));
		bullets20[i].setTexture("img/PNG/Lasers/laser20.png"); bullets_20[i].setTexture("img/PNG/Lasers/laser_20.png");
		bullets20[i].setPosition(Container(-100.0f, -100.0f)); bullets_20[i].setPosition(Container(-100.0f, -100.0f));
		bullets30[i].setTexture("img/PNG/Lasers/laserBlue01(left).png"); bullets_30[i].setTexture("img/PNG/Lasers/laserBlue01(right).png");
		bullets30[i].setPosition(Container(-100.0f, -100.0f)); bullets_30[i].setPosition(Container(-100.0f, -100.0f));
	}
	
	tex.loadFromFile(png_path);
	left.setTexture(leftT); right.setTexture(rightT); sprite.setTexture(tex);
	fireT.loadFromFile("img/ship.png"); fireLT.loadFromFile("img/ship(left).png");fireRT.loadFromFile("img/ship(right).png");
	powerT.loadFromFile("img/ship2.png"); powerLT.loadFromFile("img/ship2(left).png"); powerRT.loadFromFile("img/ship2(right).png");
	x = 340;y = 600;
	sprite.setPosition(x, y);
	sprite.setScale(0.75, 0.75);
	left.setScale(0.75, 0.75);
	right.setScale(0.75, 0.75);
}
void Player::setTextureRect(int w, int x, int y, int z)
{
	this->sprite.setTextureRect(IntRect(w, x, y, z));
}
Container Player::getPosition()
{
	return Container(this -> sprite.getPosition().x, this -> sprite.getPosition().y);
}
int Player::getLives()
{
	return Player::lives;
}
void Player::setTextureRect(FloatRect f)
{
	this->sprite.setTextureRect(IntRect(f.left, f.top, f.width, f.height));
}
Player::~Player() {
	delete[] this->bullets;
	delete[] this->bullets10;
	delete[] this->bullets_10;
	delete[] this->bullets20;
	delete[] this->bullets_20;
	delete[] this->bullets30;
	delete[] this->bullets_30;
}
void Player::fire() {
	if (!this->isPowered) {
		bullets[bulletInd].setSprite(this->mov_dir, this -> fireBullets);
		bullets[bulletInd].setPosition(Container(this->sprite.getPosition().x + (this->sprite.getLocalBounds().width / 2) - 20,
			this->sprite.getPosition().y - 30 + (this->sprite.getLocalBounds().height / 2)));
		bullets[bulletInd].setShow();
		bulletInd += 1;
	}
	else {
		bullets[bulletInd].setSprite("", false);
		bullets[bulletInd].setPosition(Container(this->sprite.getPosition().x + (this->sprite.getLocalBounds().width / 2) - 20,
			this->sprite.getPosition().y - 30 + (this->sprite.getLocalBounds().height / 2)));
		bullets[bulletInd].setShow();
		bullets10[bulletInd].setPosition(Container(this->sprite.getPosition().x + (this->sprite.getLocalBounds().width / 2) - 20,
			this->sprite.getPosition().y - 30 + (this->sprite.getLocalBounds().height / 2)));
		bullets10[bulletInd].setShow();
		bullets_10[bulletInd].setPosition(Container(this->sprite.getPosition().x + (this->sprite.getLocalBounds().width / 2) - 20,
			this->sprite.getPosition().y - 30 + (this->sprite.getLocalBounds().height / 2)));
		bullets_10[bulletInd].setShow();
		bullets20[bulletInd].setPosition(Container(this->sprite.getPosition().x + (this->sprite.getLocalBounds().width / 2) - 20,
			this->sprite.getPosition().y - 30 + (this->sprite.getLocalBounds().height / 2)));
		bullets20[bulletInd].setShow();
		bullets_20[bulletInd].setPosition(Container(this->sprite.getPosition().x + (this->sprite.getLocalBounds().width / 2) - 20,
			this->sprite.getPosition().y - 30 + (this->sprite.getLocalBounds().height / 2)));
		bullets_20[bulletInd].setShow();
		bullets30[bulletInd].setPosition(Container(this->sprite.getPosition().x + (this->sprite.getLocalBounds().width / 2) - 20,
			this->sprite.getPosition().y - 30 + (this->sprite.getLocalBounds().height / 2)));
		bullets30[bulletInd].setShow();
		bullets_30[bulletInd].setPosition(Container(this->sprite.getPosition().x + (this->sprite.getLocalBounds().width / 2) - 20,
			this->sprite.getPosition().y - 30 + (this->sprite.getLocalBounds().height / 2)));
		bullets_30[bulletInd].setShow();
		bulletInd += 1;
	}
	if (bulletInd == bSize) bulletInd = 0;
}

void Player::useAddOn(float time, AddOn* addOn) {
	if (addOn != nullptr) this->addOn = addOn;
	if (this->addOn == nullptr) return;
	if (this->addOn->getType() == "PowerUp") {
		if (!this->isPowered) this->isPowered = true;
		else {
			this->sprite.setTexture(powerT);this->left.setTexture(powerLT); this->right.setTexture(powerRT);
			this->addOnDuration += time;
			if (this->addOnDuration >= 5.0) {
				left.setTexture(leftT); right.setTexture(rightT); sprite.setTexture(tex);
				this->isPowered = false;
				this->addOnDuration = 0.0;
				this->addOn = nullptr;
				this->bulletInd = 0;
			}
		}
	}
	else if (this->addOn->getType() == "Fire") {
		if (!this -> fireBullets) this->fireBullets = true;
		this->addOnDuration += time;
		this->sprite.setTexture(fireT);this->left.setTexture(fireLT); this->right.setTexture(fireRT);
		if (this->addOnDuration >= 5.0) {
			left.setTexture(leftT); right.setTexture(rightT); sprite.setTexture(tex);
			this->fireBullets = false;
			this->addOnDuration = 0.0;
			this->addOn = nullptr;
		}
		
	}
	else if (this->addOn->getType() == "Life") {
		Player::addLife();
		this->addOn = nullptr;
	}
	else if (this->addOn->getType() == "Danger") {
		this->destroying = true;
	}
}

FloatRect Player::getGlobalBounds() const
{
	return this -> sprite.getGlobalBounds();
}

void Player::destroy() {
	this->sprite.setPosition(-300.0f, -100.0f);
}

void Player::updateDestroying(float dt) {
	this->animation.update(row, dt, true);
	this->sprite.setTexture(this->destroyT);
	this->sprite.setTextureRect(animation.rectangle);
	if (this->animation.getCurrentImage().x == 8 && this -> animation.getCurrentImage().y == 8) {
		this->destroy();
	}
}

Container Player::move(std::string s) {
	float delta_x = 0, delta_y = 0;
	if (s == "l") {
		if (speedX > -this -> topSpeed)
			speedX -= acc;
		//delta_x = -1;
	}
	else if (s == "r") {
		//delta_x = 1;
		if (speedX < this -> topSpeed)
		speedX += acc;
	}
	if (s == "u") {
		//delta_y = -1;
		if (speedY > -this->topSpeed)
			speedY -= acc;
	}
	else if (s == "d") {
		//delta_y = 1;
		if (speedY < this->topSpeed)
		speedY += acc;
	}

	sprite.move(speedX, speedY);
	if (this->sprite.getPosition().x > float(WIDTH)) {
		this->sprite.setPosition(-this->sprite.getLocalBounds().width, this->sprite.getPosition().y);
	}
	else if (this->sprite.getPosition().x < -this -> sprite.getLocalBounds().width) {
		this->sprite.setPosition(float(WIDTH), this->sprite.getPosition().y);
	}
	if (this->sprite.getPosition().y > float(HEIGHT)) {
		this->sprite.setPosition(this -> sprite.getPosition().x, -this->sprite.getLocalBounds().height);
	}
	else if (this->sprite.getPosition().y < -this->sprite.getLocalBounds().height) {
		this->sprite.setPosition(this->sprite.getPosition().x, float(HEIGHT));
	}
	return Container(delta_x, delta_y);
}

void Player::setLives(int n) {
	Player::lives = n;
}

void Player::writeToFile(ofstream& file)
{
	float n, m; n = this->sprite.getPosition().x;m = this->sprite.getPosition().y;
	file.write(reinterpret_cast<char*>(&n), sizeof(float));
	file.write(reinterpret_cast<char*>(&m), sizeof(float));
	file.write(reinterpret_cast<char*>(&lives), sizeof(int));
	file.write(reinterpret_cast<char*>(&destroying), sizeof(bool));
	file.write(reinterpret_cast<char*>(&topSpeed), sizeof(float));
	file.write(reinterpret_cast<char*>(&acc), sizeof(float));
	file.write(reinterpret_cast<char*>(&number), sizeof(int));
	int x = score.getNum(); file.write(reinterpret_cast<char*>(&x), sizeof(int));
	for (int i = 0; i < bSize; i++) {
		this->bullets[i].writeToFile(file);
	}
	file.write(reinterpret_cast<char*>(&addOnDuration), sizeof(float));
	file.write(reinterpret_cast<char*>(&isPowered), sizeof(bool));
	file.write(reinterpret_cast<char*>(&fireBullets), sizeof(bool));

}

void Player::readFromFile(ifstream& file)
{
	float n, m;
	file.read(reinterpret_cast<char*>(&n), sizeof(float));
	file.read(reinterpret_cast<char*>(&m), sizeof(float));
	this->sprite.setPosition(n, m);
	file.read(reinterpret_cast<char*>(&lives), sizeof(int));
	file.read(reinterpret_cast<char*>(&destroying), sizeof(bool));
	file.read(reinterpret_cast<char*>(&topSpeed), sizeof(float));
	file.read(reinterpret_cast<char*>(&acc), sizeof(float));
	file.read(reinterpret_cast<char*>(&number), sizeof(int));
	int x; file.read(reinterpret_cast<char*>(&x), sizeof(int)); score.setNum(x);
	for (int i = 0; i < bSize; i++) {
		this->bullets[i].readFromFile(file);
	}
	file.read(reinterpret_cast<char*>(&addOnDuration), sizeof(float));
	file.read(reinterpret_cast<char*>(&isPowered), sizeof(bool));
	file.read(reinterpret_cast<char*>(&fireBullets), sizeof(bool));
	if (this->isPowered) this->addOn = new PowerUp("img/PNG/Power-ups/shield_gold.png");
	if (this -> fireBullets) this -> addOn = new Fire("img/PNG/Power-ups/powerupRed_bolt.png");
}

void Player::setSpaceShip()
{
	switch (this -> number) {
		case 1:
			this->sprite.setTexture(tex);
			this->right.setTexture(rightT);
			this->left.setTexture(leftT);
			this->acc = 0.0001;
			this->topSpeed = 0.5;
			break;
		case 2:
			this->sprite.setTexture(op2);
			this->right.setTexture(op2R);
			this->left.setTexture(op2L);
			this->acc = 0.0007;
			this->topSpeed = 0.1;
			break;
		case 3:
			this->sprite.setTexture(op3);
			this->right.setTexture(op3R);
			this->left.setTexture(op3L);
			this->acc = 0.0005;
			this->topSpeed = 0.2;
			break;
		default:
			break;
	}
}

bool Player::intersects(FloatRect r1, FloatRect r2) {
	float x1 = r1.left + r1.width / 2;
	float y1 = r1.top + r1.height / 2;

	float x2 = r2.left + r2.width / 2;
	float y2 = r2.top + r2.height / 2;

	return (abs(x1 - x2) < (r1.width / 2 + r2.width / 2)) && (abs(y1 - y2) < (r1.height / 2 + r2.height / 2));
}

bool Player::collides(const Bullet& other) {
	return intersects(sprite.getGlobalBounds(), other.getGlobalBounds());
}
bool Player::collides(Enemy& e) {
	return intersects(sprite.getGlobalBounds(), e.getGlobalBounds());
}
bool Player::collides(AddOn* other) {
	if (other == nullptr) return false;
	return this->intersects(sprite.getGlobalBounds(), other->getBody().getGlobalBounds());
}


