#pragma once

#include <SFML/Graphics.hpp>
#include "NumDisplay.h"
#include <time.h>
#include "Levels.h"
#include "Fire.h"
#include "Danger.h"
#include "Monster.h"
#include "Dragon.h"
#include "Life.h"
#include "Alpha.h"
#include "Beta.h"
#include "Gamma.h"
#include "PowerUp.h"
#include "player.h"
const char title[] = "OOP-Project, Spring-2023";

using namespace sf;

class Game
{
private:
    int WIDTH = 750, HEIGHT = 660;
    //some texts and ui things here
    Font font, font2;
    Text nextLevel;
    Levels level;
    Sprite background, lives, speechBubble; //Game background sprite
    Texture speech, life;
private:
    Container dxdy;
    float enemyMoveTime = 0;
    float addOnTime = 0;
    float enemyDx = 5.0f;
    float monsterTime, dragonTime;
    bool monsterComing, DragonComing;
private:
    //vars used for animation
    Texture destroy, collider;
    Sprite destruction, leftCollider, rightCollider;
    Animation desAnim;
    bool desHappening;
    float nextLevelTimer;
    bool transitionAnimationFlag = false;
    bool playerSpawn = false;
    bool enemiesComing = true;
    Container enemyPos[5][5];
    //cutscene vars
    float totalSceneTime;
    bool cutSceneEnded = false, scene1Ended = false, scene2Ended = false, scene3Ended = false;
    Texture heroT, heroineT, villainT, cageT, speechflip;
    Sprite hero, heroine, villain, cage, speechbubbleflip;
    Text talks;
public:
    //vars used for animation
public:
    AddOn* addOn;
    Invader*** enemies;
    Enemy** bosses;
    Player* p; //player 
private:
    // add other game attributes
    void generateAddOn(float time);
    void drawAddOn(RenderWindow& window);
    void drawBullets(RenderWindow& window);
    void moveBullets();
    void drawEnemies(RenderWindow& window, float dt);
    void moveEnemies(float dt, Invader& e);
    void enemyFire(float dt);
    void drawPlayer(RenderWindow& window, float dt);
    void checkEnemyCollision();
    void checkPlayerCollision();
    bool checkAllDestroyed();
    void makeNewEnemies();
    void renderCutScene(RenderWindow& window, float time);
    void enemiesForm(float dt);
public:
    void writeToFile(ofstream& file);
    void readFromFile(ifstream& file);
    void restart();
    Game();
    void start_game(RenderWindow& window, float, float, string&, int&, int);
    ~Game();
};



