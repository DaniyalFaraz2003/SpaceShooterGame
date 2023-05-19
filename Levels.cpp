#include "Levels.h"

Levels::Levels() {
	this->levelNumber = 0;
	this->wave = 0;
}

void Levels::initEnemies(Invader ***enemies) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			enemies[i][j]->setShow(false);
			enemies[i][j]->setPos(Container(750 / 2 - 50, 660 / 2 - 50));
		}
	}
}

void Levels::rectangle(Invader*** enemies) {
	initEnemies(enemies);
	for (int i = 0; i < 5; i++) {
		enemies[i][0]->setShow(true);
		enemies[i][4]->setShow(true);
		enemies[0][i]->setShow(true);
		enemies[4][i]->setShow(true);
	}
}

void Levels::circle(Invader*** enemies) {
	initEnemies(enemies);
	enemies[0][2]->setShow(true); enemies[1][3]->setShow(true);
	enemies[4][2]->setShow(true); enemies[2][3]->setShow(true);
	enemies[1][1]->setShow(true); enemies[3][3]->setShow(true);
	enemies[2][1]->setShow(true);
	enemies[3][1]->setShow(true);
}

void Levels::diamond(Invader*** enemies) {
	initEnemies(enemies);
	enemies[0][2]->setShow(true); enemies[2][0]->setShow(true);
	enemies[1][1]->setShow(true); enemies[3][1]->setShow(true);
	enemies[4][2]->setShow(true); enemies[3][3]->setShow(true);
	enemies[2][4]->setShow(true); enemies[1][3]->setShow(true);
}
void Levels::triangle(Invader*** enemies) {
	initEnemies(enemies);
	enemies[0][2]->setShow(true); enemies[2][1]->setShow(true);
	enemies[2][3]->setShow(true);
	for (int i = 0; i < 5; i++) enemies[4][i]->setShow(true);
}
void Levels::cross(Invader*** enemies) {
	initEnemies(enemies);
	for (int i = 0; i < 5; i++) {
		enemies[i][i]->setShow(true);
		enemies[i][4 - i]->setShow(true);
	}
}
void Levels::filled(string shape, Invader*** enemies) {
	initEnemies(enemies);
	if (shape == "rectangle") {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) enemies[i][j]->setShow(true);
		}
	}
	else if (shape == "triangle") {
		for (int i = 0; i < 5; i++) {
			enemies[i][2]->setShow(true);
			enemies[4][i]->setShow(true);
		}
		enemies[2][1]->setShow(true); enemies[3][1]->setShow(true);
		enemies[2][3]->setShow(true); enemies[3][3]->setShow(true);
	}
	else if (shape == "diamond") {
		this->diamond(enemies);
		enemies[2][1]->setShow(true); enemies[2][3]->setShow(true);
		for (int i = 1; i < 4; i++) enemies[i][2]->setShow(true);
	}
	else if (shape == "circle") {
		this->circle(enemies);
		for (int i = 1; i < 4; i++) enemies[i][2]->setShow(true);
	}
	else if (shape == "heart") {
		enemies[1][0]->setShow(true);enemies[0][1]->setShow(true);
		enemies[1][2]->setShow(true);enemies[0][3]->setShow(true);
		enemies[1][4]->setShow(true);enemies[3][3]->setShow(true);
		enemies[4][2]->setShow(true);enemies[3][1]->setShow(true);
		enemies[1][1]->setShow(true);enemies[2][1]->setShow(true);
		enemies[2][2]->setShow(true);enemies[3][2]->setShow(true);
		enemies[1][3]->setShow(true);enemies[2][3]->setShow(true);
	}
}