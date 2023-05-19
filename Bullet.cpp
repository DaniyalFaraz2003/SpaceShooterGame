#include "Bullet.h"
Bullet::Bullet(string path) {
	leftT.loadFromFile("img/PNG/lasers/laserBlue01(left).png");
	this -> straightT.loadFromFile("img/PNG/lasers/laserBlue01.png");
	rightT.loadFromFile("img/PNG/lasers/laserBlue01(right).png");
	this->left.setTexture(leftT); this->right.setTexture(rightT);
	straight.setTexture(straightT);
	rtf.loadFromFile("img/PNG/lasers/laserRed16(right).png"); ltf.loadFromFile("img/PNG/lasers/laserRed16(left).png"), stf.loadFromFile("img/PNG/lasers/laserRed16.png");
	sf.setTexture(stf); rf.setTexture(rtf); lf.setTexture(ltf);
	show = false;
}
void Bullet::draw(RenderWindow& window) {
	if (show) {
		window.draw(this->body);
	}
}
void Bullet::writeToFile(ostream& file)
{
	position.x = this->body.getPosition().x; position.y = this ->body.getPosition().y;
	file.write(reinterpret_cast<char*>(&position.x), sizeof(float));
	file.write(reinterpret_cast<char*>(&position.y), sizeof(float));
	file.write(reinterpret_cast<char*>(&show), sizeof(bool));
}
void Bullet::readFromFile(istream& file)
{
	file.read(reinterpret_cast<char*>(&position.x), sizeof(float));
	file.read(reinterpret_cast<char*>(&position.y), sizeof(float));
	file.read(reinterpret_cast<char*>(&show), sizeof(bool));
	this->setPosition(this->position);
}
void Bullet::setSprite(string dir, bool isFire) {
	if (dir == "left") {
		if (isFire) {
			this->body = lf;
		}
		else this->body = left;
	}
	else if (dir == "right") {
		if (isFire) {
			this->body = rf;
		}
		else this->body = right;
	}
	else {
		if (isFire) {
			this->body = sf;
		}
		else this->body = straight;
	}
	this->move_dir = dir;
}
void Bullet::setShow() {
	show = true;
}
void Bullet::setTexture(string path) {
	this->straightT.loadFromFile(path);
	this->body.setTexture(this->straightT);
}
Container Bullet::getPosition() {
	return Container(this->body.getPosition().x, this->body.getPosition().y);
}
void Bullet::setPosition(Container pos) {
	this->body.setPosition(pos.x, pos.y);
}
void Bullet::move(float xFactor, float yFactor) {
	if (show)
		this->body.move(xFactor, yFactor);
}


void Bullet::hasCollided()
{
	this->destroy();
	this->setPosition(Container(-100, -100));
}

FloatRect Bullet::getGlobalBounds() const
{
	return this -> body.getGlobalBounds();
}



bool Bullet::isOutOfGame() {
	if (this->body.getPosition().x < -this->body.getGlobalBounds().width) return true;
	else if (this->body.getPosition().x > 750) return true;
	else if (this->body.getPosition().y < 0.0f - this -> body.getLocalBounds().height) return true;
	return false;
}
void Bullet::destroy() {
	this->setPosition(Container(-100.0f, -100.0f));
	this->show = false;
}