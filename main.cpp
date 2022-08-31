#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector> 
//#include "TextureManager.h"
//#include "Random.h"
#include "Helpers.h"
#include "Board.h"
//#include "Tiles.h"

using namespace std;

int main()
{
    vector<int> config;
    readConfig(config);

    Board board = Board(config[0], config[1], config[2]);

    sf::RenderWindow window(sf::VideoMode(config[0] * 32, (config[1] * 32) + 100), "Minesweeper");
    window.setKeyRepeatEnabled(false);

    while (window.isOpen())
    {
        //Exit Condition
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        //click
        if (event.type == sf::Event::MouseButtonPressed)
        {
            //right click
            if ((event.mouseButton.button == sf::Mouse::Right) && !board.checkWin() && !board.checkLose())
            {
                int row = event.mouseButton.y / 32;
                int col = event.mouseButton.x / 32;
                if ((col < config[0] && row < config[1]))
                {
                    board.flagTile(row, col);
                    event.type = sf::Event::KeyPressed;
                    board.checkWin();
                }
            }
            //left click
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                int row = event.mouseButton.y / 32;
                int col = event.mouseButton.x / 32;
                if (board.getSmile().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    board.reset();
                    event.type = sf::Event::KeyPressed;
                }
                if (board.getDebug().getGlobalBounds().contains(mousePosition.x, mousePosition.y) &&!board.checkWin() && !board.checkLose())
                {
                    board.Debug();
                    event.type = sf::Event::KeyPressed;
                }
                if (board.getTest(1).getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    string file = "boards/testboard1.brd";
                    board.loadTest(file);
                    event.type = sf::Event::KeyPressed;
                }
                if (board.getTest(2).getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    string file = "boards/testboard2.brd";
                    board.loadTest(file);
                    event.type = sf::Event::KeyPressed;
                }
                if (board.getTest(3).getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    string file = "boards/testboard3.brd";
                    board.loadTest(file);
                    event.type = sf::Event::KeyPressed;
                }
                if ((col < config[0] && row < config[1]) && !board.checkWin() && !board.checkLose())
                {
                    board.revealTile(board.tiles[row][col]);
                    event.type = sf::Event::KeyPressed;
                    board.checkWin();
                }
            }
        }



        window.clear();
        board.Draw(window);
        window.display();
    }
    TextureManager::Clear();
    return 0;
}