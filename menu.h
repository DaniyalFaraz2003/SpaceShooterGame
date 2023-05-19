#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
#include <iostream>
#include <fstream>
#include "game.h"
class Menu {
private:
    Animation bgAnim;
    const int WIDTH = 750;
    const int HEIGHT = 660;
    int currentItem;
    Texture selecterT, back, gridT, t;
    Sprite selecterL, selecterR, background, grid, temp;
    Font font;
    Text menu[6], gameOverText;
    int totalOps = 6;
    string* names; int* scores; int size = 0;
private:
    void extend(string name, int score);
    void up();
    void sortArrays();
    void down();
public:
    //add menu attributes here
    Menu();
    ~Menu();
    void display_menu();
};
