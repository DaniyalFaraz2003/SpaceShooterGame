#include "menu.h"
Menu::Menu() : bgAnim(nullptr, Container(5, 36), 0.05f)
{
    back.loadFromFile("img/spritesheet.png");
    bgAnim.rectangle.width = this->back.getSize().x / float(bgAnim.getImageCount().x);
    bgAnim.rectangle.height = this->back.getSize().y / float(37);
    t.loadFromFile("img/third.png"); temp.setTexture(t);
    selecterT.loadFromFile("img/select.png");
    selecterL.setTexture(selecterT); selecterR.setTexture(selecterT);
    selecterL.setPosition(160.0f, HEIGHT / (totalOps + 1) * (1));
    selecterR.setPosition(selecterL.getPosition().x + 360, selecterL.getPosition().y);
    currentItem = 0;
    if (!font.loadFromFile("font/Space Game.otf"))
    {
        std::cout << "Can't open font" << endl;
        return;
    }

    for (int i = 0; i < totalOps; i++) {
        menu[i].setFont(font); menu[i].setFillColor(Color::White);
        menu[i].setPosition(WIDTH / 2 - 120, HEIGHT / (totalOps + 1) * (i + 1));
        menu[i].setCharacterSize(50);
    }
    menu[0].setString("START"); menu[0].move(170 - 110, 0.0);
    menu[1].setString("RESTART"); menu[1].move(170 - 140, 0.0);
    menu[2].setString("HELP"); menu[2].move(170 - 90, 0.0);
    menu[3].setString("HIGHSCORES"); menu[3].move(10, 0.0);
    menu[4].setString("CHANGE SHIP"); menu[4].setPosition(WIDTH / 2 - 110, menu[4].getPosition().y);
    menu[5].setString("EXIT"); menu[5].move(170 - 90, 0.0);
    //gridT.loadFromFile("img/OIP.png"); grid.setTexture(gridT);
    //back.loadFromFile("img/Grid2.png"); 
    background.setTexture(back); background.setOrigin(0, 440 / 2);
    background.setPosition(0, 330);
    background.setScale(1.5, 1.5);
    gameOverText.setFont(font); gameOverText.setCharacterSize(50);
    gameOverText.setPosition(20, 50);
}

void Menu::up() {
    if (currentItem - 1 >= 0) {
        currentItem--;    
        selecterL.setPosition(160.0f, HEIGHT / (totalOps + 1) * (currentItem + 1));
        selecterR.setPosition(selecterL.getPosition().x + 360, selecterL.getPosition().y);
    }
}

void Menu::down() {
    if (currentItem + 1 < totalOps) {
        currentItem++;
        selecterL.setPosition(160.0f, HEIGHT / (totalOps + 1) * (currentItem + 1));
        selecterR.setPosition(selecterL.getPosition().x + 360, selecterL.getPosition().y);
    }
}

Menu::~Menu() {}

void Menu::sortArrays() {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (this->scores[i] > this->scores[j]) {
                int temp = this->scores[i]; string tempName = this->names[i];
                this->scores[i] = this->scores[j]; this->names[i] = this->names[j];
                this->scores[j] = temp; this->names[j] = tempName;
            }
        }
    }
}



void Menu::extend(string name, int score)
{
    int n = this->size;
    int* temp1 = new int[n + 1];
    string* temp2 = new string[n + 1];
    for (int i = 0; i < n; i++) {
        temp1[i] = scores[i];
        temp2[i] = names[i];
    }
    temp1[n] = score; temp2[n] = name;
    this->size += 1;
    delete[] this->scores;
    delete[] this->names;
    this->scores = temp1;
    this->names = temp2;
}

void Menu::display_menu()

{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "MY GAME"), savedGameSelect(VideoMode(400, 200), "Saved Game Detected");
    Game g;
    Text someText, instructions, title;
    Clock clock;
    bool changeShip = false, isSavedAvailable = false, outlineBig = true, outlineSmall = false, showMenu = false, inGame = false, helpScreen = false, highScores = false, gameOver = false, saveGame = false;;
    float timer = 0;
    int finalScore = 100;
    unsigned int animationRow = 0, shipNumber = 1;
    ifstream read, reader;
    ofstream write, writer;
    string endGameState = "", nameOfPlayer;
    Texture t1, t2, t3, ship1, ship2, ship3; 
    Sprite first, second, third, shipSelect;
    Music music;
    Font font2; font2.loadFromFile("font/TechnoRaceItalic-eZRWe.otf");
    RectangleShape bar, border; bar.setSize(Vector2f(250, 20)); bar.setFillColor(Color::Red); border.setSize(Vector2f(250, 20)); border.setOutlineThickness(10);border.setOutlineColor(Color::Black);
    Text arrows, titleSelection, attrs; arrows.setFont(font2); arrows.setCharacterSize(200); arrows.setString("<\t\t\t  >");arrows.setPosition(0, 220);
    titleSelection.setFont(font2); titleSelection.setCharacterSize(70); titleSelection.setString("CHANGE SHIP"); titleSelection.setPosition(180, 50);
    attrs.setFont(font2); attrs.setCharacterSize(50); attrs.setString("DAMAGE:\n\nTOP SPEED:\n\nACCELERATION:");attrs.setPosition(380, 200);
    ship1.loadFromFile("img/mship1.png"); ship2.loadFromFile("img/option2.png"); ship3.loadFromFile("img/option3.png");
    shipSelect.setScale(2.0, 2.0);
    shipSelect.setTexture(ship1);shipSelect.setPosition(100, 250);
    
    someText.setFont(font); someText.setCharacterSize(40);
    someText.setPosition(20, 300); 
    instructions.setFont(font2); instructions.setCharacterSize(20); title.setFont(font);
    instructions.setPosition(0, 0);title.setCharacterSize(70); title.setPosition(130, 20); title.setString("GALAXY INVASION");
    title.setOutlineThickness(0); title.setFillColor(Color::Cyan); title.setOutlineColor(Color::Color(224, 208, 64)); 
    instructions.setString(
        "  MOVEMENT:\n  Use the arrow keys to move your spaceship around.\n\n  FIRE:\n  Press The 'F' key to fire.\n\n  ENEMIES:\n  There are three types of enemies. Invader, Monster, Boss. Invader is of three types.\n  Alpha, Beta, Gamma. Destroy them to score points. Dodge the monster and final\n  boss to score more points.\n\n  ADD ONS:\n  Four type of objects will fall. Take the sheild and red energy to get special power.\n  Take the small spaceship to get one extra life. Dodge the meteor to get points.\n\n  DEATH:\n  You will die upon collision with meteor, enemy bullets and enemies. Dying will cost you a \n  life so watch out.\n\n  WINNNING:\n  Defeat the final boss to win the game. In the end you will recieve a badge if your score is\n  high enough.");

    //Binary file
    read.open("saved.dat", ios::in | ios::binary);
    if (read.peek() == EOF) {
        savedGameSelect.close(); showMenu = true;
    }
    else isSavedAvailable = true;
    //ends here
    t1.loadFromFile("img/first.png"); t2.loadFromFile("img/second.png");
    t3.loadFromFile("img/third.png");
    first.setTexture(t1); second.setTexture(t2); third.setTexture(t3);
    first.setPosition(3, 240); second.setPosition(3, 315); third.setPosition(3, 395);

    //First reading from file
    reader.open("highscores.txt", ios::in);
    music.openFromFile("song/MUSIC.ogg");
    music.setLoop(true);
    music.play();
    if (reader.is_open()) {
        string line;
        while (getline(reader, line)) {
            string name, score;
            int i;
            for (i = 0; line[i] != '-'; i++) {
                name += line[i];
            }
            i++;
            for (i; line[i] != '\0'; i++) {
                score += line[i];
            }
            int scoreNum = 0;
            for (int i = 0; score[i] != '\0'; i++) {
                scoreNum *= 10;
                scoreNum += int(score[i] - '0');
            }
            extend(name, scoreNum);
        }
        sortArrays();
    }
    reader.close();
    //reading operation finished
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        if (showMenu) {
            if (endGameState == "WIN" || endGameState == "LOSE") {
                this->menu[0].setString("START");
                menu[0].setPosition(WIDTH / 2 - 60, menu[0].getPosition().y);
            }
            window.clear(Color::Black);
            this->bgAnim.update(animationRow, time, true);
            this->background.setTextureRect(bgAnim.rectangle);
            window.draw(background);
            for (int i = 0; i < totalOps; i++) window.draw(menu[i]);
            window.draw(selecterL); window.draw(selecterR);
            if (outlineBig) {
                int n = title.getOutlineThickness();
                title.setOutlineThickness(n + 1);
                if (n >= 10.0) {
                    outlineSmall = true;
                    outlineBig = false;
                }
            }
            if (outlineSmall) {
                int n = title.getOutlineThickness();
                title.setOutlineThickness(n - 1);
                if (n <= 0.0) {
                    outlineSmall = false;
                    outlineBig = true;
                }
            }
            window.draw(title);
            window.display();
            if (endGameState == "WIN" || endGameState == "LOSE") {
                endGameState = "";
                nameOfPlayer = "";
                inGame = false;
                g.restart();
            }
        }
        else if (inGame) {
            window.clear(Color::Black);
            this->bgAnim.update(animationRow, time, true);
            this->background.setTextureRect(bgAnim.rectangle);
            window.draw(background);
            g.start_game(window, time, timer, endGameState, finalScore, shipNumber);
            window.display();
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                showMenu = true;
                inGame = false;
                saveGame = true;
            }
            if (endGameState == "WIN" || endGameState == "LOSE") {
                gameOver = true; inGame = false; showMenu = false;
            }
            continue;
        }
        else if (helpScreen) {
            window.clear(Color::Black);
            window.draw(background);
            this->bgAnim.update(animationRow, time, true);
            this->background.setTextureRect(bgAnim.rectangle);
            window.draw(background);
            window.draw(instructions);
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                helpScreen = false;
                showMenu = true;
                inGame = false;
            }
            window.display();
        }
        else if (highScores) {
            window.clear(Color::Black);
            window.draw(background);
            this->bgAnim.update(animationRow, time, true);
            this->background.setTextureRect(bgAnim.rectangle);
            window.draw(background);
            gameOverText.setString("                 HIGHSCORES");
            someText.setPosition(70, 200);
            someText.setString("NAME                                 SCORE");
            Text name, score; name.setFont(font); score.setFont(font);
            name.setCharacterSize(30); score.setCharacterSize(30);
            if (this->size > 6) {
                for (int i = 0; i < 5; i++) {
                    name.setString(this->names[i]); score.setString(to_string(this->scores[i]));
                    name.setPosition(70, 250 + (i * 80)); score.setPosition(600, 250 + (i * 80));
                    window.draw(name); window.draw(score);
                }
            }
            else {
                for (int i = 0; i < this->size; i++) {
                    name.setString(this->names[i]); score.setString(to_string(this->scores[i]));
                    name.setPosition(70, 250 + (i * 80)); score.setPosition(600, 250 + (i * 80));
                    window.draw(name); window.draw(score);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                helpScreen = false; highScores = false;
                showMenu = true;
                inGame = false;
            }
            window.draw(first); window.draw(second); window.draw(third);
            window.draw(someText);
            window.draw(gameOverText);
            window.display();
        }
        else if (gameOver) {
            window.clear(Color::Black);
            window.draw(background);
            this->bgAnim.update(animationRow, time, true);
            this->background.setTextureRect(bgAnim.rectangle);
            window.draw(background);
            if (endGameState == "WIN") gameOverText.setString("         Congratulations!!!\n   You finished the game!");
            if (endGameState == "LOSE") gameOverText.setString("           You lost the game!");
            someText.setString("Your Score : " + to_string(finalScore) + "\n\nName: " + nameOfPlayer);
            window.draw(gameOverText);
            window.draw(someText);
            window.display();
        }
        else if (changeShip) {
            window.clear(Color::Black);
            this->bgAnim.update(animationRow, time, true);
            this->background.setTextureRect(bgAnim.rectangle);
            window.draw(background);
            int px1 = 390, py1 = 280, py2 = 420, py3 = 560;
            switch (shipNumber) {
            case 1:
                shipSelect.setTexture(ship1);
                bar.setPosition(px1, py1);border.setPosition(px1, py1);
                bar.setSize(Vector2f(100, 20));
                window.draw(border);
                window.draw(bar);
                bar.setPosition(px1, py2);border.setPosition(px1, py2);
                bar.setSize(Vector2f(200, 20));
                window.draw(border);
                window.draw(bar);
                bar.setPosition(px1, py3);border.setPosition(px1, py3);
                bar.setSize(Vector2f(50, 20));
                window.draw(border);
                window.draw(bar);
                break;
            case 2:
                shipSelect.setTexture(ship2);
                bar.setPosition(px1, py1);border.setPosition(px1, py1);
                bar.setSize(Vector2f(200, 20));
                window.draw(border);
                window.draw(bar);
                bar.setPosition(px1, py2);border.setPosition(px1, py2);
                bar.setSize(Vector2f(70, 20));
                window.draw(border);
                window.draw(bar);
                bar.setPosition(px1, py3);border.setPosition(px1, py3);
                bar.setSize(Vector2f(120, 20));
                window.draw(border);
                window.draw(bar);
                break;
            case 3:
                shipSelect.setTexture(ship3);
                bar.setPosition(px1, py1);border.setPosition(px1, py1);
                bar.setSize(Vector2f(90, 20));
                window.draw(border);
                window.draw(bar);
                bar.setPosition(px1, py2);border.setPosition(px1, py2);
                bar.setSize(Vector2f(130, 20));
                window.draw(border);
                window.draw(bar);
                bar.setPosition(px1, py3);border.setPosition(px1, py3);
                bar.setSize(Vector2f(200, 20));
                window.draw(border);
                window.draw(bar);
                break;
            default:
                break;
            }
            window.draw(titleSelection);
            window.draw(arrows);
            window.draw(attrs);
            window.draw(shipSelect);

            window.display();
        }
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
            if (e.type == Event::KeyPressed) {
                switch (e.key.code) {
                case Keyboard::Up:
                    up();
                    break;

                case Keyboard::Down:
                    down();
                    break;
                case Keyboard::Enter:
                    if (currentItem == 0) {
                        menu[0].setString("RESUME"); menu[0].setPosition(WIDTH / 2 - 80, menu[0].getPosition().y);
                        inGame = true; helpScreen = false; showMenu = false;
                    }
                    if (currentItem == 1) {
                        g.restart();
                        inGame = true; showMenu = false; helpScreen = false;
                    }
                    if (currentItem == 2) {
                        inGame = false; showMenu = false; helpScreen = true;
                    }
                    if (currentItem == 3) {
                        showMenu = false;
                        highScores = true;
                    }
                    if (currentItem == 4) {
                        showMenu = false;
                        changeShip = true;
                        continue;
                    }
                    if (currentItem == 5) {
                        window.close();
                    }
                    break;
                default:
                    break;
                }
                if (gameOver) {
                    if ((char(e.key.code) >= Keyboard::A && char(e.key.code) <= Keyboard::Z) || (e.key.code == Keyboard::Space)) {
                        nameOfPlayer += (e.key.code == Keyboard::Space) ? ' ' : char(e.key.code) + 65;
                    }
                    if (e.key.code == Keyboard::BackSpace) {
                        if (nameOfPlayer != "") nameOfPlayer.pop_back();

                    }
                    if (e.key.code == Keyboard::Enter) {
                        extend(nameOfPlayer, finalScore);
                        sortArrays();
                        writer.open("highscores.txt", ios::out);
                        if (writer.is_open()) {
                            for (int i = 0; i < this->size; i++) {
                                writer << this->names[i] + '-' + to_string(this->scores[i]) << endl;
                            }
                        }
                        writer.close();
                        gameOver = false; showMenu = true;
                    }
                }
                if (changeShip) {
                    if (e.key.code == Keyboard::Right) {
                        shipNumber++;
                        if (shipNumber > 3) shipNumber = 1;
                    }
                    if (e.key.code == Keyboard::Left) {
                        shipNumber--;
                        if (shipNumber <= 0) shipNumber = 3;
                    }
                    if (e.key.code == Keyboard::Escape) {
                        showMenu = true; changeShip = false;
                    }
                }
            }
        }
        if (saveGame) {
            write.open("saved.dat", ios::out | ios::binary);
            write.write(reinterpret_cast<char*>(&shipNumber), sizeof(int));
            g.writeToFile(write);
            write.close();
            saveGame = false;
        }
        if (isSavedAvailable) {
            Text something; something.setFont(font2);
            something.setCharacterSize(30);
            something.setFillColor(Color::Black);
            something.setString("   A saved game is detected.\nWould you like to play that one? \n\n                YES                     NO");
            RectangleShape selector; selector.setSize(Vector2f(80, 50));
            selector.setOutlineThickness(10); selector.setOutlineColor(Color::Black);
            selector.setPosition(80, 120);
            while (savedGameSelect.isOpen()) {
                Event event;
                while (savedGameSelect.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        savedGameSelect.close();
                        isSavedAvailable = false;
                    }
                    else if (event.type == Event::KeyPressed) {
                        switch (event.key.code)
                        {
                        case Keyboard::Right:
                            selector.setPosition(250, 120);
                            break;
                        case Keyboard::Left:
                            selector.setPosition(80, 120);
                            break;
                        case Keyboard::Enter:
                            if (selector.getPosition().x == 80) {
                                reader.open("saved.dat", ios::in | ios::binary);
                                reader.read(reinterpret_cast<char*>(&shipNumber), sizeof(int));
                                g.readFromFile(reader);
                                reader.close();
                                showMenu = true;
                                isSavedAvailable = false;
                                savedGameSelect.close();
                            }
                            if (selector.getPosition().x == 250) {
                                showMenu = true;
                                isSavedAvailable = false;
                                savedGameSelect.close();
                            }
                        default:
                            break;
                        }
                    }
                }
                savedGameSelect.clear(Color::White);
                savedGameSelect.draw(selector);
                savedGameSelect.draw(something);
                savedGameSelect.display();
            }
        }
    }

    //display menu screen here

    // add functionality of all the menu options here

    //if Start game option is chosen 

    //g.start_game();



}