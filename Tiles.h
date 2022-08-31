#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector> 
#include "TextureManager.h"
//#include "Random.h"
//#include "Helpers.h"
using namespace std;

class Tile
{
	int row = 0, col = 0;
	sf::Sprite hidden;
	sf::Sprite revealed;
	sf::Sprite number[8];
	sf::Sprite flagS;
	sf::Sprite mineS;
	bool mine = 0, reveal = 0, flag = 0, debug = 0;
public:
	vector<Tile*> adjacentTiles;
	Tile();
	Tile(int x, int y);
	void Draw(sf::RenderWindow& window);
	void DrawMine(sf::RenderWindow& window);
	void findAdjacent(vector<vector<Tile*>>& tiles);
	int adjacentBomb();
	//Accessors
	bool checkMine();
	bool checkFlag();
	bool checkReveal();
	bool checkDebug();
	sf::Sprite getSprite();
	//Modifier
	void toggleMine();
	void toggleFlag();
	void toggleReveal();
	void toggleDebug();
	void reset();
};
