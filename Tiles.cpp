#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector> 
#include "Tiles.h"
using namespace std;

Tile::Tile()
{
	row = 0;
	col = 0;
	hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
	revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	for (unsigned int i = 0; i < 8; i++)
	{
		string num = "number_";
		num += to_string(i + 1);
		number[i].setTexture(TextureManager::GetTexture(num));
	}
	flagS.setTexture(TextureManager::GetTexture("flag"));
	mineS.setTexture(TextureManager::GetTexture("mine"));
}

Tile::Tile(int row_, int col_)
{
	row = row_;
	col = col_;
	hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
	hidden.setPosition(col * 32, row * 32);
	revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	for (unsigned int i = 0; i < 8; i++)
	{
		string num = "number_";
		num += to_string(i+1);
		number[i].setTexture(TextureManager::GetTexture(num));
	}
	flagS.setTexture(TextureManager::GetTexture("flag"));
	mineS.setTexture(TextureManager::GetTexture("mine"));
}

void Tile::Draw(sf::RenderWindow& window)
{
	//hidden.setPosition(col * 32, row * 32);
	window.draw(hidden);
	if (flag)
	{
		flagS.setPosition(col * 32, row * 32);
		window.draw(flagS);
	}
	if (reveal && !mine)
	{
		if (adjacentBomb() == 0)
		{
			revealed.setPosition(col * 32, row * 32);
			window.draw(revealed);
		}
		else
		{
			revealed.setPosition(col * 32, row * 32);
			number[adjacentBomb() - 1].setPosition(col * 32, row * 32);
			window.draw(revealed);
			window.draw(number[adjacentBomb() - 1]);
		}
	}
	if (reveal && mine)
	{
		revealed.setPosition(col * 32, row * 32);
		window.draw(revealed);
		DrawMine(window);
	}
	if (debug)
	{
		if (mine)
		{
			DrawMine(window);
		}
	}
}

void Tile::DrawMine(sf::RenderWindow& window)
{
	mineS.setPosition(col * 32, row * 32);
	window.draw(mineS);
}

void Tile::findAdjacent(vector<vector<Tile*>>& tiles)
{
	//cout << tiles.size() << " " << tiles[1].size();
	//upper left
	if (row == 0 && col == 0)
	{
		adjacentTiles.push_back(tiles[row][col+1]);
		adjacentTiles.push_back(tiles[row + 1][col]);
		adjacentTiles.push_back(tiles[row + 1][col + 1]);
	}
	//upper right
	else if (row == 0 && col == (tiles[1].size() - 1))
	{
		adjacentTiles.push_back(tiles[row][col - 1]);
		adjacentTiles.push_back(tiles[row + 1][col - 1]);
		adjacentTiles.push_back(tiles[row + 1][col]);
	}
	//lower right
	else if (row == (tiles.size() - 1) && col == (tiles[1].size() - 1))
	{
		adjacentTiles.push_back(tiles[row - 1][col]);
		adjacentTiles.push_back(tiles[row - 1][col - 1]);
		adjacentTiles.push_back(tiles[row][col - 1]);
	}
	//lower left
	else if (row == (tiles.size() - 1) && col == 0)
	{
		adjacentTiles.push_back(tiles[row][col + 1]);
		adjacentTiles.push_back(tiles[row - 1][col + 1]);
		adjacentTiles.push_back(tiles[row - 1][col]);
	}
	//upper
	else if (row == 0)
	{
		adjacentTiles.push_back(tiles[row][col + 1]);
		adjacentTiles.push_back(tiles[row][col - 1]);
		adjacentTiles.push_back(tiles[row + 1][col - 1]);
		adjacentTiles.push_back(tiles[row + 1][col]);
		adjacentTiles.push_back(tiles[row + 1][col + 1]);
	}
	//right
	else if (col == (tiles[1].size() - 1))
	{
		adjacentTiles.push_back(tiles[row - 1][col]);
		adjacentTiles.push_back(tiles[row - 1][col - 1]);
		adjacentTiles.push_back(tiles[row][col - 1]);
		adjacentTiles.push_back(tiles[row + 1][col - 1]);
		adjacentTiles.push_back(tiles[row + 1][col]);
	}
	//lower
	else if (row == (tiles.size() - 1))
	{
		adjacentTiles.push_back(tiles[row][col + 1]);
		adjacentTiles.push_back(tiles[row - 1][col + 1]);
		adjacentTiles.push_back(tiles[row - 1][col]);
		adjacentTiles.push_back(tiles[row - 1][col - 1]);
		adjacentTiles.push_back(tiles[row][col - 1]);
	}
	//left
	else if (col == 0)
	{
		adjacentTiles.push_back(tiles[row][col + 1]);
		adjacentTiles.push_back(tiles[row - 1][col + 1]);
		adjacentTiles.push_back(tiles[row - 1][col]);
		adjacentTiles.push_back(tiles[row + 1][col]);
		adjacentTiles.push_back(tiles[row + 1][col + 1]);
	}
	//mid
	else
	{
		adjacentTiles.push_back(tiles[row][col + 1]);
		adjacentTiles.push_back(tiles[row - 1][col + 1]);
		adjacentTiles.push_back(tiles[row - 1][col]);
		adjacentTiles.push_back(tiles[row - 1][col - 1]);
		adjacentTiles.push_back(tiles[row][col - 1]);
		adjacentTiles.push_back(tiles[row + 1][col - 1]);
		adjacentTiles.push_back(tiles[row + 1][col]);
		adjacentTiles.push_back(tiles[row + 1][col + 1]);
	}
}

int Tile::adjacentBomb()
{
	int count = 0;
	for (unsigned int i = 0; i < adjacentTiles.size(); i++)
	{
		if (adjacentTiles[i]->mine == 1)
		{
			count++;
		}
	}
	return count;
}

//Accessors
bool Tile::checkFlag() { return flag; }
bool Tile::checkMine() { return mine; }
bool Tile::checkReveal() { return reveal; }
bool Tile::checkDebug() { return debug; }
sf::Sprite Tile::getSprite() { return hidden; }

//modifiers
void Tile::toggleFlag() { flag = !flag; }
void Tile::toggleMine() { mine = 1; }
void Tile::toggleReveal() { reveal = 1; }
void Tile::toggleDebug() { debug = !debug; }
void Tile::reset()
{
	mine = 0;
	flag = 0;
	reveal = 0;
}
