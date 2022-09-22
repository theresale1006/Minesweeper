#include <iostream>
#include "Gameboard.h"

bool ClickedOn(sf::RenderWindow& window, sf::Sprite& icon) {
    return icon.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

int main()
{
    ifstream config("boards/config.cfg");
    string col, rows, bombs;
    getline(config, col);
    getline(config, rows);
    getline(config, bombs);
    sf::RenderWindow window(sf::VideoMode(stoi(col) * 32, stoi(rows) * 32 + 88), "Minesweeper");
    Board gameboard(stoi(rows), stoi(col), stoi(bombs));
    bool finished = false;
    bool win = false;
    bool debug = false;
    sf::Sprite smile(Textures::Get("face_happy"));
    sf::Sprite debugIcon(Textures::Get("debug"));
    sf::Sprite test1(Textures::Get("test_1"));
    sf::Sprite test2(Textures::Get("test_2"));
    sf::Sprite test3(Textures::Get("test_3"));
    smile.setPosition((((stof(col) - 2.0f) / 2.0f)) * 32.0f, stof(rows) * 32.0f);
    debugIcon.setPosition((((stof(col) - 2.0f) / 2.0f)) * 32.0f + 128.0f, stof(rows) * 32.0f);
    test1.setPosition((((stof(col) - 2.0f) / 2.0f)) * 32.0f + 192.0f, stof(rows) * 32.0f);
    test2.setPosition((((stof(col) - 2.0f) / 2.0f)) * 32.0f + 256.0f, stof(rows) * 32.0f);
    test3.setPosition((((stof(col) - 2.0f) / 2.0f)) * 32.0f + 320.0f, stof(rows) * 32.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (ClickedOn(window, smile)) {
                        gameboard.Clear();
                        gameboard.CreateTiles("");
                        finished = false;
                        win = false;
                        smile.setTexture(Textures::Get("face_happy"));
                    }
                    if (ClickedOn(window, debugIcon) && !win) {
                        if (debug)
                            debug = false;
                        else
                            debug = true;
                    }
                    if (ClickedOn(window, test1)) {
                        gameboard.Clear();
                        gameboard.CreateTiles("testboard1");
                        finished = false;
                        win = false;
                        smile.setTexture(Textures::Get("face_happy"));
                    }
                    if (ClickedOn(window, test2)) {
                        gameboard.Clear();
                        gameboard.CreateTiles("testboard2");
                        finished = false;
                        win = false;
                        smile.setTexture(Textures::Get("face_happy"));
                    }
                    if (ClickedOn(window, test3)) {
                        gameboard.Clear();
                        gameboard.CreateTiles("testboard3");
                        finished = false;
                        win = false;
                        smile.setTexture(Textures::Get("face_happy"));
                    }
                    if (sf::Mouse::getPosition(window).y < stoi(rows) * 32 && sf::Mouse::getPosition(window).x < stoi(col) * 32 && !win && !finished) {
                        if (gameboard.Reveal(sf::Mouse::getPosition(window).y / 32, sf::Mouse::getPosition(window).x / 32)) {
                            finished = true;
                            gameboard.RevealBomb();
                            smile.setTexture(Textures::Get("face_lose"));
                        }
                        if (gameboard.Win()) {
                            win = true;
                            debug = false;
                            smile.setTexture(Textures::Get("face_win"));
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                    if (sf::Mouse::getPosition(window).y < stoi(rows) * 32 && sf::Mouse::getPosition(window).x < stoi(col) * 32 && !win && !finished)
                        gameboard.Flag(sf::Mouse::getPosition(window).y / 32, sf::Mouse::getPosition(window).x / 32);
            }
        }

        window.clear();
        gameboard.Draw(window, (finished || debug));
        window.draw(smile);
        window.draw(debugIcon);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        window.display();
    }

    Textures::Clear();
    return 0;
}