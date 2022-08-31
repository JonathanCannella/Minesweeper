#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector> 
#include "Random.h"
#include "Tiles.h"

class Board {
	int row, col, mineCount, ogcount;
	int cond = 0;
	bool win = 0, lose = 0;
	sf::Sprite face, digits, debug, test_1, test_2, test_3;
	sf::Sprite counter[11];
public:
	vector<vector<Tile*>> tiles;
	Board();
	Board(int width, int height, int _mineCount);
	void Draw(sf::RenderWindow& window);
	void DrawCount(sf::RenderWindow& window);
	void setFace(int cond);
	void flagTile(int row, int col);
	void revealTile(Tile*& tile);
	void loadTest(string& file);
	void reset();
	void Debug();
	Tile* tileAt(int row, int col);
	//accessors
	sf::Sprite getSmile();
	sf::Sprite getDebug();
	sf::Sprite getTest(int num);
	bool checkWin();
	bool checkLose();
};
