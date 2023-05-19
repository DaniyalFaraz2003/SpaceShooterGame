#include "game.h"
#include <time.h>
#include <iostream>
using namespace std;
Game::Game():desAnim(nullptr, Container(6, 1), 0.1f)
{
    font.loadFromFile("font/TechnoRaceItalic-eZRWe.otf");
    //initializing for cutsCene
    cutSceneEnded = false;
    speechflip.loadFromFile("img/speechFlipped.png");
    heroT.loadFromFile("img/mship1.png"); heroineT.loadFromFile("img/PNG/playerShip2_red.png");villainT.loadFromFile("img/boss.png");cageT.loadFromFile("img/cage.png");
    hero.setTexture(heroT); heroine.setTexture(heroineT); villain.setTexture(villainT); cage.setTexture(cageT);
    hero.setPosition(375, 660), heroine.setPosition(230, 660); villain.setPosition(230, -300); cage.setPosition(130, -300);
    talks.setFont(font); talks.setCharacterSize(10); talks.setFillColor(Color::Black);
    speechbubbleflip.setTexture(speechflip);
    //for game
    srand(time(0));
    
    destroy.loadFromFile("img/animExp1(cropped).png"); collider.loadFromFile("img/beta.png");
    leftCollider.setTexture(collider); rightCollider.setTexture(collider);
    destruction.setTexture(destroy);
    destruction.setScale(2.0, 2.0);
    leftCollider.setScale(2.5, 2.5); rightCollider.setScale(2.5, 2.5);
    leftCollider.setPosition(-200, 330); rightCollider.setPosition(750, 330); destruction.setPosition(-1000, -1000);
    desAnim.rectangle.width = this->destroy.getSize().x / float(desAnim.getImageCount().x);
    desAnim.rectangle.height = this->destroy.getSize().y / float(desAnim.getImageCount().y);
    desHappening = false;
    speech.loadFromFile("img/speechBubble.png"); speechBubble.setTexture(speech); speechBubble.setPosition(-200, -200); speechbubbleflip.setPosition(-200, -200);
    life.loadFromFile("img/life.png");
    lives.setTexture(life);
    font.loadFromFile("font/TechnoRaceItalic-eZRWe.otf");
    font2.loadFromFile("font/astron boy.otf");
    nextLevel.setFont(font); nextLevel.setCharacterSize(50); nextLevel.setFillColor(Color::Red); nextLevel.setOutlineThickness(2);
    nextLevel.setOutlineColor(Color::Black);
    this->addOn = nullptr;
    level.levelNumber = 1; level.wave = 0;
    enemies = new Invader**[5];
    for (int i = 0; i < 5; i++) {
        enemies[i] = new Invader * [5];
        for (int j = 0; j < 5; j++) {
            int n = rand() % 3;
            if (n == 0) enemies[i][j] = new Alpha;
            else if (n == 1) enemies[i][j] = new Beta;
            else enemies[i][j] = new Gamma;
            enemyPos[i][j] = Container(120 * j + (30 + j * 30), 70 * i + (20 + i * 10));
        }
    }
    Invader::initBullets();
    bosses = new Enemy * [2];
    bosses[0] = new Monster; this->monsterComing = false;
    bosses[1] = new Dragon; this->DragonComing = false;
    p = new Player("img/mship1.png");
    level.initEnemies(enemies);
}



void Game::generateAddOn(float time) {
    this->addOnTime += time;
    if (this->addOnTime >= 15.0) {
        if (this->addOn != nullptr) delete this->addOn;
        int n = rand() % 4;
        if (n == 0) {
            this->addOn = new PowerUp("img/PNG/Power-ups/shield_gold.png");
        }
        else if (n == 1) {
            this->addOn = new Fire("img/PNG/Power-ups/powerupRed_bolt.png");
        }
        else if (n == 2) {
            this->addOn = new Danger("img/PNG/Meteors/meteorGrey_big4.png");
        }
        else {
            this->addOn = new Life("img/life.png");
        }
        this->addOn->spawn();
        this->addOnTime = 0.0;
    }
}

void Game::drawAddOn(RenderWindow& window) {
    if (this->addOn != nullptr && !(this -> addOn->getBody().getPosition().x < 0)) {
        this->addOn->fall();
        if (this->addOn->getType() == "Danger" && this->addOn->getBody().getPosition().y > 700) {
            p->score.add(5);
            delete this->addOn; this->addOn = nullptr;
        }
        if (this->addOn != nullptr) this->addOn->draw(window);
    }
}

void Game::makeNewEnemies() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            delete this->enemies[i][j];
        }
        delete[] this->enemies[i];
    }
    delete[] this->enemies;
    enemies = new Invader * *[5];
    for (int i = 0; i < 5; i++) {
        enemies[i] = new Invader * [5];
        for (int j = 0; j < 5; j++) {
            int n = rand() % 3;
            if (n == 0) enemies[i][j] = new Alpha;
            else if (n == 1) enemies[i][j] = new Beta;
            else enemies[i][j] = new Gamma;
            enemies[i][j]->setFireInterval(enemies[i][j]->getFireInterval() - (0.6 * this->level.levelNumber));
        }
    }
}

void Game::writeToFile(ofstream& file)
{
    file.write(reinterpret_cast<char*>(&level.wave), sizeof(int));
    file.write(reinterpret_cast<char*>(&level.levelNumber), sizeof(int));
    file.write(reinterpret_cast<char*>(&addOnTime), sizeof(float));
    file.write(reinterpret_cast<char*>(&monsterTime), sizeof(float));
    file.write(reinterpret_cast<char*>(&dragonTime), sizeof(float));
    file.write(reinterpret_cast<char*>(&monsterComing), sizeof(bool));
    file.write(reinterpret_cast<char*>(&DragonComing), sizeof(bool));
    file.write(reinterpret_cast<char*>(&nextLevelTimer), sizeof(float));
    file.write(reinterpret_cast<char*>(&transitionAnimationFlag), sizeof(bool));
    file.write(reinterpret_cast<char*>(&playerSpawn), sizeof(bool));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            enemies[i][j]->writeToFile(file);
        }
    }
    p->writeToFile(file);
}

void Game::readFromFile(ifstream& file)
{
    file.read(reinterpret_cast<char*>(&level.wave), sizeof(int));
    file.read(reinterpret_cast<char*>(&level.levelNumber), sizeof(int));
    file.read(reinterpret_cast<char*>(&addOnTime), sizeof(float));
    file.read(reinterpret_cast<char*>(&monsterTime), sizeof(float));
    file.read(reinterpret_cast<char*>(&dragonTime), sizeof(float));
    file.read(reinterpret_cast<char*>(&monsterComing), sizeof(bool));
    file.read(reinterpret_cast<char*>(&DragonComing), sizeof(bool));
    file.read(reinterpret_cast<char*>(&nextLevelTimer), sizeof(float));
    file.read(reinterpret_cast<char*>(&transitionAnimationFlag), sizeof(bool));
    file.read(reinterpret_cast<char*>(&playerSpawn), sizeof(bool));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            enemies[i][j]->readFromFile(file);
        }
    }
    p->readFromFile(file);
}

void Game::restart()
{
    level.levelNumber = 1; level.wave = 0; delete this->addOn;
    this->addOn = nullptr;
    this->p->score.setNum(0); this->p->setLives(3);
    this->makeNewEnemies(); level.rectangle(enemies);
    this->monsterComing = false; this->monsterTime = 0;
    this->DragonComing = false; this->dragonTime = 0;
    this->addOnTime = 0; this->bosses[0]->setFireInterval(0);
    this->bosses[1]->setFireInterval(0); delete this->p;
    level.initEnemies(enemies);
    p = new Player("img/mship1.png");
}



void Game::moveBullets() {
    if (!this->p->isPowered) {
        for (int i = 0; i < p->bSize; i++) {
            if (p->bullets[i].move_dir == "left")
                p->bullets[i].move(-0.37f, -0.5f);
            else if (p->bullets[i].move_dir == "right")
                p->bullets[i].move(0.37f, -0.5f);
            else
                p->bullets[i].move(0.0f, -0.5f);
            if (p->bullets[i].isOutOfGame()) {
                p->bullets[i].destroy();
            }
            //make remaining bullets go
            if (!p -> bullets10[i].isOutOfGame()) p->bullets10[i].move(-0.123f, -0.5f);
            if (p->bullets10[i].isOutOfGame()) {
                p->bullets10[i].destroy();
            }
            if (!p->bullets_10[i].isOutOfGame()) p->bullets_10[i].move(0.123f, -0.5f);
            if (p->bullets_10[i].isOutOfGame()) {
                p->bullets_10[i].destroy();
            }
            if (!p->bullets20[i].isOutOfGame()) p->bullets20[i].move(-0.246f, -0.5f);
            if (p->bullets20[i].isOutOfGame()) {
                p->bullets20[i].destroy();
            }
            if (!p->bullets_10[i].isOutOfGame()) p->bullets_20[i].move(0.246f, -0.5f);
            if (p->bullets_20[i].isOutOfGame()) {
                p->bullets_20[i].destroy();
            }
            if (!p->bullets30[i].isOutOfGame()) p->bullets30[i].move(-0.37f, -0.5f);
            if (p->bullets30[i].isOutOfGame()) {
                p->bullets30[i].destroy();
            }
            if (!p->bullets_30[i].isOutOfGame()) p->bullets_30[i].move(0.37f, -0.5f);
            if (p->bullets_30[i].isOutOfGame()) {
                p->bullets_30[i].destroy();
            }
        }
    }
    else {
        for (int i = 0; i < p->bSize; i++) {
            p->bullets[i].move(0.0f, -0.5f);
            if (p->bullets[i].isOutOfGame()) {
                p->bullets[i].destroy();
            }
            p->bullets10[i].move(-0.123f, -0.5f);
            if (p->bullets10[i].isOutOfGame()) {
                p->bullets10[i].destroy();
            }
            p->bullets_10[i].move(0.123f, -0.5f);
            if (p->bullets_10[i].isOutOfGame()) {
                p->bullets_10[i].destroy();
            }
            p->bullets20[i].move(-0.246f, -0.5f);
            if (p->bullets20[i].isOutOfGame()) {
                p->bullets20[i].destroy();
            }
            p->bullets_20[i].move(0.246f, -0.5f);
            if (p->bullets_20[i].isOutOfGame()) {
                p->bullets_20[i].destroy();
            }
            p->bullets30[i].move(-0.37f, -0.5f);
            if (p->bullets30[i].isOutOfGame()) {
                p->bullets30[i].destroy();
            }
            p->bullets_30[i].move(0.37f, -0.5f);
            if (p->bullets_30[i].isOutOfGame()) {
                p->bullets_30[i].destroy();
            }
        }
    }
    for (int k = 0; k < Invader::bSize; k++) {
        Invader::bullets[k].move(0.0f, 0.1f);
        if (Invader::bullets[k].isOutOfGame()) {
            Invader::bullets[k].destroy();
        }
    }
}
void Game::drawPlayer(RenderWindow& window, float dt) {
    if (p->destroying) {
        this->p->updateDestroying(dt);
        window.draw(this->p->sprite);
        return;
    }
    if (this->p->mov_dir == "straight") {
        window.draw(this->p->sprite);
    }
    else if (this->p->mov_dir == "left") {
        this->p->left.setPosition(this->p->sprite.getPosition());
        window.draw(this->p->left);
    }
    else if (this->p->mov_dir == "right") {
        this->p->right.setPosition(this->p->sprite.getPosition());
        window.draw(this->p->right);
    }
}
void Game::drawEnemies(RenderWindow& window, float dt)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (enemies[i][j]->getShow()) {
                if (this->enemies[i][j]->getDestroying()) {
                    this->enemies[i][j]->updateDestroying(dt);
                }
                enemies[i][j]->draw(window);
            }
        }
    }
}
bool Game::checkAllDestroyed() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (this->enemies[i][j]->getShow()) return false;
        }
    }
    return true;
}
void Game::checkEnemyCollision() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (!this->p->isPowered) {
                for (int k = 0; k < p->bSize; k++) {
                    if (this->enemies[i][j]->collides(p->bullets[k]) && !this->enemies[i][j]->getDestroying() && this ->enemies[i][j]->getShow()) {
                        if (this -> enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        if (!this -> p -> fireBullets) p->bullets[k].hasCollided();
                        break;
                    }
                    if (!p->bullets10[k].isOutOfGame() && this->enemies[i][j]->collides(p->bullets10[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets10[k].hasCollided();
                        break;
                    }
                    if (!p->bullets_10[k].isOutOfGame() && this->enemies[i][j]->collides(p->bullets_10[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets_10[k].hasCollided();
                        break;
                    }
                    if (!p->bullets20[k].isOutOfGame() && this->enemies[i][j]->collides(p->bullets20[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets20[k].hasCollided();
                        break;
                    }
                    if (!p->bullets_20[k].isOutOfGame() && this->enemies[i][j]->collides(p->bullets_20[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets_20[k].hasCollided();
                        break;
                    }
                    if (!p->bullets30[k].isOutOfGame() && this->enemies[i][j]->collides(p->bullets30[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets30[k].hasCollided();
                        break;
                    }
                    if (!p->bullets_30[k].isOutOfGame() && this->enemies[i][j]->collides(p->bullets_30[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets_30[k].hasCollided();
                        break;
                    }
                }
            }
            else {
                for (int k = 0; k < p->bSize; k++) {
                    if (this->enemies[i][j]->collides(p->bullets[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets[k].hasCollided();
                        break;
                    }
                    if (this->enemies[i][j]->collides(p->bullets10[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets10[k].hasCollided();
                        break;
                    }
                    if (this->enemies[i][j]->collides(p->bullets_10[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets_10[k].hasCollided();
                        break;
                    }
                    if (this->enemies[i][j]->collides(p->bullets20[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets20[k].hasCollided();
                        break;
                    }
                    if (this->enemies[i][j]->collides(p->bullets_20[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets_20[k].hasCollided();
                        break;
                    }
                    if (this->enemies[i][j]->collides(p->bullets30[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets30[k].hasCollided();
                        break;
                    }
                    if (this->enemies[i][j]->collides(p->bullets_30[k]) && !this->enemies[i][j]->getDestroying() && this->enemies[i][j]->getShow()) {
                        if (this->enemies[i][j]->getType() == "alpha") this->p->score.add(10 * level.levelNumber);
                        else if (this->enemies[i][j]->getType() == "beta") this->p->score.add(20 * level.levelNumber);
                        else this->p->score.add(30 * level.levelNumber);
                        this->enemies[i][j]->setDestroying(true);
                        p->bullets_30[k].hasCollided();
                        break;
                    }
                }
            }
        }
    }
}

void Game::enemiesForm(float dt) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            //if (enemies[i][j]->getShow()) {
            float initX = this->enemies[i][j]->getPos().x, initY = this->enemies[i][j]->getPos().y;
            float newPosX = initX + (enemyPos[i][j].x - initX) * 0.01;
            float newPosY = initY + (enemyPos[i][j].y - initY) * 0.01;
            if (!(enemies[i][j]->getPos() == enemyPos[i][j])) {
                this->enemies[i][j]->setPos(Container(newPosX, newPosY));
            }
            //}
        }
    }
}

void Game::checkPlayerCollision() {
    if (this->p->collides(this->addOn)) {
        this->addOn->getBody().setPosition(-400, -100);
        this->p->useAddOn(0, this->addOn);
    }
    if (!this->p->isPowered) {
        if (monsterComing) {
            if (this->p->intersects(this->p->getGlobalBounds(), this->bosses[0]->getGlobalBounds())
                || this->p->intersects(this->p->getGlobalBounds(), this->bosses[0]->getGlobalBounds_beam()))
                p->destroying = true; return;
        }
        if (DragonComing) {
            if (this->p->intersects(this->p->getGlobalBounds(), this->bosses[1]->getGlobalBounds())
                || this->p->intersects(this->p->getGlobalBounds(), this->bosses[1]->getGlobalBounds_beam()))
                p->destroying = true; return;
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (this->p->collides(*enemies[i][j]) && !p->destroying && enemies[i][j]->getShow()) {
                    p->destroying = true;
                    return;
                }
            }
        }
        for (int k = 0; k < Invader::bSize; k++) {
            if (this->p->collides(Invader::bullets[k]) && !p->destroying) {
                p->destroying = true;
                Invader::bullets[k].destroy();
                return;
            }
        }
    }
}

void Game::enemyFire(float dt) {
    int i = rand() % 5, j = rand() % 5;
    if (enemies[i][j]->getShow())
    enemies[i][j]->fire(dt);
}

void Game::drawBullets(RenderWindow& window) {
    if (!this->p->isPowered) {
        for (int i = 0; i < p->bSize; i++) {
            p->bullets[i].draw(window);
            if (!p->bullets10[i].isOutOfGame()) p->bullets10[i].draw(window); if (!p->bullets_10[i].isOutOfGame()) p->bullets_10[i].draw(window);
            if (!p->bullets20[i].isOutOfGame()) p->bullets20[i].draw(window); if (!p->bullets_20[i].isOutOfGame()) p->bullets_20[i].draw(window);
            if (!p->bullets30[i].isOutOfGame()) p->bullets30[i].draw(window); if (!p->bullets_30[i].isOutOfGame()) p->bullets_30[i].draw(window);
        }
    }
    else {
        for (int i = 0; i < p->bSize; i++) {
            p->bullets[i].draw(window);
            p->bullets10[i].draw(window); p->bullets_10[i].draw(window);
            p->bullets20[i].draw(window); p->bullets_20[i].draw(window);
            p->bullets30[i].draw(window); p->bullets_30[i].draw(window);
        }
    }
    for (int k = 0; k < Invader::bSize; k++) {
        Invader::bullets[k].draw(window);
    }
}

void Game::renderCutScene(RenderWindow& window, float time) {
    totalSceneTime += time;
    Event e;
    while (window.pollEvent(e)) {
        if (e.type == Event::Closed) window.close();
        if (e.type == Event::KeyPressed) {
            if (e.key.code == Keyboard::A) {
                playerSpawn = true;
                cutSceneEnded = true;
            }
        }
    }
    // Update the cutscene based on the elapsed time

    if (!scene1Ended)
    {
        // Update scene 1 of the cutscene
        // ...
        hero.move(0.0, -0.006);heroine.move(0.0, -0.006);
        if (totalSceneTime > 5.0 && totalSceneTime < 8.0) {
            
            talks.setString("The space looks so \ncalm and wonderful \ndoesn't it?");talks.setCharacterSize(15);
            talks.setFillColor(Color::Black); talks.setFont(font);
            speechbubbleflip.setPosition(hero.getPosition().x + 80, hero.getPosition().y - 110);
            talks.setPosition(speechbubbleflip.getPosition().x + 15, speechbubbleflip.getPosition().y + 20);
            talks.setOutlineThickness(0);
            speechbubbleflip.setScale(1.0, 1.0);
            speechBubble.setPosition(-200, -200);
        }
        if (totalSceneTime > 8.0 && totalSceneTime < 11.0) {
            talks.setString("Yes it's so peaceful\ni am glad we can\nspend time \ntogether");talks.setCharacterSize(15);
            talks.setFillColor(Color::Black); talks.setFont(font);
            speechBubble.setPosition(heroine.getPosition().x - 110, heroine.getPosition().y - 110);
            talks.setPosition(speechBubble.getPosition().x + 15, speechBubble.getPosition().y + 20);
            talks.setOutlineThickness(0);
            speechBubble.setScale(1.0, 1.0);
            speechbubbleflip.setPosition(-200, -200);
        }
        if (totalSceneTime > 11 && totalSceneTime < 14) {
            talks.setString("I cherish every\nmoment we have.\nYou make \neverything brighter");talks.setCharacterSize(15);
            talks.setFillColor(Color::Black); talks.setFont(font);
            speechbubbleflip.setPosition(hero.getPosition().x + 80, hero.getPosition().y - 110);
            talks.setPosition(speechbubbleflip.getPosition().x + 15, speechbubbleflip.getPosition().y + 20);
            talks.setOutlineThickness(0);
            speechbubbleflip.setScale(1.0, 1.0);
            speechBubble.setPosition(-200, -200);
        }
        window.draw(hero);window.draw(heroine);window.draw(speechbubbleflip);window.draw(speechBubble);window.draw(talks);
        if (totalSceneTime >= 14)
        {
            // Perform any necessary actions when scene 1 finishes
            // ...
            speechBubble.setPosition(-200, -200);
            speechbubbleflip.setPosition(-200, -200);
            talks.setPosition(-200, -200);
            scene1Ended = true;
            totalSceneTime = 0;
        }
    }
    else if (!scene2Ended)
    {
        if (totalSceneTime > 0 && totalSceneTime < 1.5) {
            villain.move(0.0, 0.1);
            if (villain.getPosition().y > 40) villain.move(0.0 ,-0.1);
        }
        if (totalSceneTime > 2 && totalSceneTime < 5) {
            talks.setString("Well well well\nWhat do we have\nhere.");talks.setCharacterSize(15);
            talks.setFillColor(Color::Black); talks.setFont(font);
            speechbubbleflip.setPosition(villain.getPosition().x + 250, villain.getPosition().y - 50);
            talks.setPosition(speechbubbleflip.getPosition().x + 15, speechbubbleflip.getPosition().y + 20);
            talks.setOutlineThickness(0);
            speechbubbleflip.setScale(1.0, 1.0);
            speechBubble.setPosition(-200, -200);
            heroine.move(0.01, 0.01);
        }
        if (totalSceneTime > 5 && totalSceneTime < 8) {
            talks.setString("A lovey-dovey\ncouple enjoying\ntheir little\nstroll");
        }
        if (totalSceneTime > 8 && totalSceneTime < 11) {
            talks.setString("Who are you?\nWhat do you.\nwant?");talks.setCharacterSize(15);
            talks.setFillColor(Color::Black); talks.setFont(font);
            speechbubbleflip.setPosition(hero.getPosition().x + 80, hero.getPosition().y - 110);
            talks.setPosition(speechbubbleflip.getPosition().x + 15, speechbubbleflip.getPosition().y + 20);
            talks.setOutlineThickness(0);
            speechbubbleflip.setScale(1.0, 1.0);
            speechBubble.setPosition(-200, -200);
        }
        if (totalSceneTime > 11 && totalSceneTime < 14) {
            talks.setString("I'm here to make\nthings\ninteresting.");talks.setCharacterSize(15);
            talks.setFillColor(Color::Black); talks.setFont(font);
            speechbubbleflip.setPosition(villain.getPosition().x + 250, villain.getPosition().y - 50);
            talks.setPosition(speechbubbleflip.getPosition().x + 15, speechbubbleflip.getPosition().y + 20);
            talks.setOutlineThickness(0);
            speechbubbleflip.setScale(1.0, 1.0);
            speechBubble.setPosition(-200, -200);
        }
        if (totalSceneTime > 14 && totalSceneTime < 17) {
            talks.setString("Say goodbye to\nyour precious\ncompanion!");
        }
        window.draw(hero);window.draw(heroine);window.draw(speechbubbleflip);window.draw(speechBubble);window.draw(talks);window.draw(villain);
        if (totalSceneTime >= 17.0)
        {
            totalSceneTime = 0;
            scene2Ended = true;
        }
    }
    else if (!scene3Ended)
    {
        if (totalSceneTime > 0 && totalSceneTime < 15) {
            float dirX = heroine.getPosition().x - cage.getPosition().x;
            float dirY = heroine.getPosition().y - cage.getPosition().y;
            cage.setScale(0.75, 0.75);
            float length = sqrt(dirX * dirX + dirY * dirY);
            dirX /= length; dirY /= length;
            cage.move(dirX * 0.05 - 0.011, dirY * 0.05 - 0.011);
            if (cage.getPosition().x >= heroine.getPosition().x - 50 && cage.getPosition().y > heroine.getPosition().y - 50) {
                cage.move(-dirX * 0.05 - 0.013, -dirY * 0.05 - 0.013);
            }
        }
        if (totalSceneTime > 10 && totalSceneTime < 20) {
            cage.move(-0.005, -0.05); heroine.move(-0.005, -0.05);
            talks.setString("HELP!!!\nSOMEONE!!\nHELP ME\nLEEEOOOON!!!");talks.setCharacterSize(15);
            talks.setFillColor(Color::Black); talks.setFont(font);
            speechBubble.setPosition(heroine.getPosition().x - 110, heroine.getPosition().y - 110);
            talks.setPosition(speechBubble.getPosition().x + 15, speechBubble.getPosition().y + 20);
            talks.setOutlineThickness(0);
            speechBubble.setScale(1.0, 1.0);
            window.draw(speechBubble);
            window.draw(talks);
            villain.move(0.0, -0.05);
            talks.setString("HAHAHAH!!\nHAHAH!!!\nHAHAHA!!!");talks.setCharacterSize(15);
            talks.setFillColor(Color::Black); talks.setFont(font);
            speechbubbleflip.setPosition(villain.getPosition().x + 250, villain.getPosition().y - 50);
            talks.setPosition(speechbubbleflip.getPosition().x + 15, speechbubbleflip.getPosition().y + 20);
            talks.setOutlineThickness(0);
            speechbubbleflip.setScale(1.0, 1.0);
            if (speechbubbleflip.getPosition().y < 0) speechbubbleflip.move(0.0, 0.05);
            if (totalSceneTime > 15 && totalSceneTime < 20) {
                talks.setString("Don't worry\nAshley. I am \ncoming for you!");talks.setCharacterSize(15);
                talks.setFillColor(Color::Black); talks.setFont(font);
                speechbubbleflip.setPosition(hero.getPosition().x + 80, hero.getPosition().y - 110);
                talks.setPosition(speechbubbleflip.getPosition().x + 15, speechbubbleflip.getPosition().y + 20);
                talks.setOutlineThickness(0);
                speechbubbleflip.setScale(1.0, 1.0);
                speechBubble.setPosition(-200, -200);
            }
        }
        if (totalSceneTime > 20 && totalSceneTime < 20.5) {
            speechBubble.setPosition(-200, -200);speechbubbleflip.setPosition(-200, -200);talks.setPosition(-200, -200);
            hero.move(0.0, 0.008);
        }
        if (totalSceneTime > 20.5 && totalSceneTime < 21.5) {
            hero.move(0.0, -0.15);
        }
        window.draw(hero);window.draw(heroine);window.draw(speechbubbleflip);window.draw(talks);window.draw(villain);window.draw(cage);

        if (totalSceneTime >= 21.5)
        {
            
            totalSceneTime = 0;
            scene3Ended = true;
        }
    }
    if (scene1Ended && scene2Ended&& scene3Ended)
    {
        cutSceneEnded = true;
        playerSpawn = true;
    }
}

void Game::start_game(RenderWindow& window, float time, float timer, string& gameOver, int& finalScore, int shipType)
{
    if (!cutSceneEnded) {
        renderCutScene(window, time);
        return;
    }
    if (enemiesComing) {
        enemiesForm(time);
    }
    srand(std::time(0));
    this->p->setNumber(shipType);
    this->p->setSpaceShip();
    bool moved = false;
    this->p->mov_dir = "straight";

    if (this->p->sprite.getPosition().x == -300.0f) {
        Player::subLife(); int temp = p->score.getNum();
        delete p;
        p = new Player("img/mship1.png");
        p->sprite.setPosition(300, 700); p->score.setNum(temp);
        this->playerSpawn = true;
        if (p->getLives() == 0) {
            finalScore = this->p->score.getNum();
            gameOver = "LOSE"; return;
        }
    }
    bool fire = false;

    Event e;
    while (window.pollEvent(e))
    {
        if (e.type == Event::Closed) // If cross/close is clicked/pressed
            window.close(); //close the game  
        if (e.type == Event::KeyPressed) {
            if (e.key.code == Keyboard::F) {
                fire = true;
            }
        }
        if (e.type == Event::KeyReleased) {
            if (e.key.code == Keyboard::F) {
                fire = false;
            }
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
    {
        dxdy = p->move("l"); // Player will move to left
        this->p->mov_dir = "left";
        moved = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) { // If right key is pressed
        dxdy = p->move("r");  //player will move to right
        this->p->mov_dir = "right"; moved = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {//If up key is pressed
        dxdy = p->move("u");    //player will move upwards
        moved = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) { // If down key is pressed
        dxdy = p->move("d");  //player will move downwards
        moved = true;
    }
    ////////////////////////////////////////////////
    /////  Call your functions here            ////
    //////////////////////////////////////////////
    if (!moved) {
        if (this->p->speedX > 0) this->p->speedX -= this->p->acc;
        if (this->p->speedX < 0) this->p->speedX += this->p->acc;
        if (this->p->speedY > 0) this->p->speedY -= this->p->acc;
        if (this->p->speedY < 0) this->p->speedY += this->p->acc;
        this->p->sprite.move(this -> p -> speedX, this -> p -> speedY);
        if (this->p->sprite.getPosition().x > float(750)) {
            this->p->sprite.setPosition(-this->p->sprite.getLocalBounds().width, this->p->sprite.getPosition().y);
        }
        else if (this->p->sprite.getPosition().x < -this->p->sprite.getLocalBounds().width) {
            this->p->sprite.setPosition(float(750), this->p->sprite.getPosition().y);
        }
    }
    if (playerSpawn) {
        p->sprite.move(0.0f, -0.1f);
        if (p->getPosition().y < 500) playerSpawn = false;
    }
    if (monsterComing) {
        if (this->monsterTime < 28) {
            if (this->bosses[0]->come())
                this->bosses[0]->move(0.05, 0.0);
            this->bosses[0]->fire(time);
            this->monsterTime += time;
        }
        else {
            if (this->bosses[0]->go()) {
                this->monsterComing = false;
                this->p->score.add(40);
                this->monsterTime = 0;
            }
        }
    }
    if (DragonComing) {
        if (this->dragonTime < 39.53) {
            this->bosses[1]->come();
            this->bosses[1]->fire(time, p->getPosition().y);
            this->dragonTime += time;
            if ((this->dragonTime > 5.0 && this->dragonTime < 10.0) || (this->dragonTime > 15.0 && this->dragonTime < 20.0) || (this->dragonTime > 25.0 && this->dragonTime < 30.0) || (this->dragonTime > 35.0 && this->dragonTime < 38.0)) {
                string talks[] = { " YOU DARE CHALLLENGE\n ME? PREPARE TO \n WITNESS TRUE POWER", " YOU THINK YOU CAN\n DEFEAT ME? HOW\n AMUSING", " FOOLISH MORTAL! YOUR \n FEEBLE ATTEMPTS ARE IN\n VAIN." };
                if (this->dragonTime > 35.0 && this->dragonTime < 38.0) nextLevel.setString("  I SHALL RETURN\n  HAHAHA!!");
                else nextLevel.setString(talks[int(dragonTime) / 10]);
                nextLevel.setCharacterSize(20);
                nextLevel.setFillColor(Color::Black); nextLevel.setFont(font);
                speechBubble.setPosition(40, 50);
                nextLevel.setPosition(speechBubble.getPosition().x + 20, speechBubble.getPosition().y + 20);
                nextLevel.setOutlineThickness(0);
                speechBubble.setScale(1.75, 1.0);
                window.draw(speechBubble);
                window.draw(nextLevel);
            }
        }
        else {
            if (this->bosses[1]->go()) {
                this->DragonComing = false;
                this->p->score.add(50);
                this->dragonTime = 0;
            }
        }
    }
    this->p->useAddOn(time, nullptr);
    this->generateAddOn(time);
    if (fire) p->fire();
    if (!monsterComing && !DragonComing) {
        this->checkEnemyCollision(); this->enemyFire(time);
    }
    if (!playerSpawn) this->checkPlayerCollision();
    this->moveBullets();
     //clears the screen
    this->drawAddOn(window);
    this->drawBullets(window);
    if (!monsterComing && !DragonComing) this->drawEnemies(window, time);
    else {
        if (DragonComing) this->bosses[1]->draw(window);
        else if (monsterComing) this->bosses[0]->draw(window);
    }
    this->drawPlayer(window, time);   // setting player on screen
    this->p->score.draw(window, 600, 610);
    for (int i = 0; i < Player::getLives(); i++) {
        lives.setPosition(32 * i + 20, 610);
        window.draw(lives);
    }
    if (this->checkAllDestroyed() && !monsterComing && !DragonComing) {
        if (!(this->level.wave + 1 == 4 && level.levelNumber + 1 == 2) && !(this->level.wave + 1 == 4 && level.levelNumber + 1 == 4)) {
            if (transitionAnimationFlag == false) {
                nextLevel.setPosition(-250.0f, 300.0f);
                leftCollider.setPosition(-200, 200); rightCollider.setPosition(750, 200);
                this->destruction.setPosition(-500, -500);
                this->desAnim.reset();
                desHappening = false;
                transitionAnimationFlag = true;
            }
            if (transitionAnimationFlag) {
                rightCollider.move(-0.5, 0.0);
                leftCollider.move(0.5, 0.0);
                if (leftCollider.getPosition().x > rightCollider.getPosition().x - 190) {
                    desHappening = true;
                }
                if (desHappening) {
                    leftCollider.setPosition(-200, -200); rightCollider.setPosition(-200, -200);
                    unsigned int r = 0;
                    this->desAnim.update(r, time, true);
                    this->destruction.setTextureRect(desAnim.rectangle);
                    this->destruction.setPosition(275, 150);
                }
            }
        }
        this->nextLevelTimer += time;
        if (this->level.wave + 1 == 4 && level.levelNumber + 1 == 2) {
            this->destruction.setPosition(-500, -500);
            nextLevel.setString("Oh no!\nA MONSTER!!!");nextLevel.setCharacterSize(20);
            nextLevel.setFillColor(Color::Black); nextLevel.setFont(font);
            nextLevel.setPosition(speechBubble.getPosition().x + 20, speechBubble.getPosition().y + 20);
            nextLevel.setOutlineThickness(0);
            speechBubble.setScale(1.0, 1.0);
            speechBubble.setPosition(this -> p -> getPosition().x - 110, this -> p -> getPosition().y - 110);
            window.draw(speechBubble);
        }
        else if (this->level.wave + 1 == 4 && level.levelNumber + 1 == 4) {
            this->destruction.setPosition(-1000, -1000);
            nextLevel.setString("   Oh no!\n   It's the\n   BOSS!!!");nextLevel.setCharacterSize(20);
            nextLevel.setFillColor(Color::Black); nextLevel.setFont(font);
            nextLevel.setPosition(speechBubble.getPosition().x + 20, speechBubble.getPosition().y + 20);
            nextLevel.setOutlineThickness(0);
            speechBubble.setScale(1.0, 1.0);
            speechBubble.setPosition(this->p->getPosition().x - 110, this->p->getPosition().y - 110);
            window.draw(speechBubble);
        }
        if (this->nextLevelTimer >= 2.35 || desAnim.getCurrentImage().x >= 5) {
            enemiesComing = true;
            desAnim.reset();
            this->makeNewEnemies();
            level.wave++;
            if (level.wave == 4) {
                level.levelNumber++;
                level.wave = 0;
            }
            if (level.levelNumber == 1) {
                switch (level.wave)
                {
                case 1:
                    level.rectangle(enemies);
                    break;
                case 2:
                    level.triangle(enemies);
                    break;
                case 3:
                    level.cross(enemies);
                    break;
                default:
                    level.triangle(enemies);
                }
            }
            else if (level.levelNumber == 2) {
                switch (level.wave)
                {
                case 0:
                    monsterComing = true;
                    break;
                case 1:
                    level.diamond(enemies);
                    break;
                case 2:
                    level.circle(enemies);
                    break;
                case 3:
                    level.filled("triangle", enemies);
                default:
                    break;
                }
            }
            else if (level.levelNumber == 3) {
                switch (level.wave)
                {
                case 0:
                    level.filled("heart", enemies);
                    break;
                case 1:
                    level.filled("rectangle", enemies);
                    break;
                case 2:
                    level.filled("circle", enemies);
                    break;
                case 3:
                    level.filled("diamond", enemies);
                    break;
                default:
                    level.filled("triangle", enemies);
                }
            }
            else if (level.levelNumber == 4) {
                this->DragonComing = true;
                level.levelNumber++;
            }
            else if (level.levelNumber == 5) {
                gameOver = "WIN";  finalScore = this->p->score.getNum();
                return;
            }
            this->nextLevelTimer = 0.0;
            transitionAnimationFlag = false;
        }
        if (level.levelNumber != 5) {
            window.draw(leftCollider); window.draw(rightCollider); window.draw(destruction);
            window.draw(nextLevel);
        }
    }  //Displaying all the sprites
}


Game::~Game()
{
    delete p;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            delete this->enemies[i][j];
        }
        delete[] this->enemies[i];
    }
    delete[] this->enemies;
    delete[] Invader::bullets;
}
