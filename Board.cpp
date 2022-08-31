#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector> 
#include "Board.h"
using namespace std;

Board::Board()
{
	row = 0;
	col = 0;
	mineCount = 0;
	ogcount = mineCount;


	tiles.resize(row);
	setFace(cond);
	face.setPosition(((col * 32) / 2) - 32, (row * 32));
	debug.setTexture(TextureManager::GetTexture("debug"));
	debug.setPosition(face.getPosition().x + 128, face.getPosition().y);
	test_1.setTexture(TextureManager::GetTexture("test_1"));
	test_1.setPosition(debug.getPosition().x + 64, debug.getPosition().y);
	test_2.setTexture(TextureManager::GetTexture("test_2"));
	test_2.setPosition(debug.getPosition().x + (2 * 64), debug.getPosition().y);
	test_3.setTexture(TextureManager::GetTexture("test_3"));
	test_3.setPosition(debug.getPosition().x + (3 * 64), debug.getPosition().y);

	//creating container of numbers
	for (unsigned int i = 0; i < 11; i++)
	{
		sf::Sprite counter_;
		counter_.setTexture(TextureManager::GetTexture("digits"));
		counter_.setTextureRect(sf::IntRect(i * 21, 0, 21, 32));
		counter[i] = counter_;
	}

	for (unsigned int i = 0; i < row; i++)
	{
		tiles[i].resize(col);
	}
	for (unsigned int i = 0; i < row; i++)
	{
		for (unsigned int j = 0; j < col; j++)
		{
			Tile* tile = new Tile(i, j);
			tiles[i][j] = tile;
		}
	}
	for (unsigned int i = 0; i < row; i++)
	{
		for (unsigned int j = 0; j < col; j++)
		{
			tiles[i][j]->findAdjacent(tiles);
		}
	}
	reset();
}

Board::Board(int width, int height, int _mineCount)
{
	row = height;
	col = width;
	mineCount = _mineCount;
	ogcount = mineCount;


	tiles.resize(row);
	setFace(cond);
	face.setPosition(((col*32)/ 2)-32, (row*32) );
	debug.setTexture(TextureManager::GetTexture("debug"));
	debug.setPosition(face.getPosition().x + 128, face.getPosition().y);
	test_1.setTexture(TextureManager::GetTexture("test_1"));
	test_1.setPosition(debug.getPosition().x + 64, debug.getPosition().y);
	test_2.setTexture(TextureManager::GetTexture("test_2"));
	test_2.setPosition(debug.getPosition().x + (2 * 64), debug.getPosition().y);
	test_3.setTexture(TextureManager::GetTexture("test_3"));
	test_3.setPosition(debug.getPosition().x + (3 * 64), debug.getPosition().y);

	//creating container of numbers
	for (unsigned int i = 0; i < 11; i++)
	{
		sf::Sprite counter_;
		counter_.setTexture(TextureManager::GetTexture("digits"));
		counter_.setTextureRect(sf::IntRect(i * 21, 0, 21, 32));
		counter[i] = counter_;
	}

	for (unsigned int i = 0; i < row; i++)
	{
		tiles[i].resize(col);
	}
	for (unsigned int i = 0; i < row; i++)
	{
		for (unsigned int j = 0; j < col; j++)
		{
			Tile* tile = new Tile(i, j);
			tiles[i][j] = tile;
		}
	}
	for (unsigned int i = 0; i < row; i++)
	{
		for (unsigned int j = 0; j < col; j++)
		{
			tiles[i][j]->findAdjacent(tiles);
		}
	}
	reset();
}

void Board::Draw(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < row; i++)
	{
		for (unsigned int j = 0; j < col; j++)
		{
			tiles[i][j]->Draw(window);
			//cout << i * 32;
		}
	}
	window.draw(face);
	window.draw(debug);
	window.draw(test_1);
	window.draw(test_2);
	window.draw(test_3);
	DrawCount(window);
} 

void Board::DrawCount(sf::RenderWindow& window)
{
	string mineCountS = to_string(mineCount);

	//Negative values;
	if (mineCount < 0 && mineCount > -10)
	{
		counter[10].setPosition(21, (row * 32));
		window.draw(counter[10]);
		counter[0].setPosition(42, (row * 32));
		window.draw(counter[0]);
		counter[0].setPosition(63, (row * 32));
		window.draw(counter[0]);
		int index = mineCountS[1] - '0';
		counter[index].setPosition((21 * (4)), (row * 32));
		window.draw(counter[index]);
	}
	else if (mineCount < -9 && mineCount > -100)
	{
		counter[10].setPosition(21, (row * 32));
		window.draw(counter[10]);
		counter[0].setPosition(42, (row * 32));
		window.draw(counter[0]);
		for (unsigned int i = 1; i < mineCountS.size(); i++)
		{
			int index = mineCountS[i] - '0';
			counter[index].setPosition((21 * (i + 2)), (row * 32));
			window.draw(counter[index]);
		}
	}
	else if (mineCount < -99)
	{
		counter[10].setPosition(21, (row * 32));
		window.draw(counter[10]);
		for (unsigned int i = 1; i < mineCountS.size(); i++)
		{
			int index = mineCountS[i] - '0';
			counter[index].setPosition((21 * (i + 2)), (row * 32));
			window.draw(counter[index]);
		}
	}
	//Positive values;
	else if (mineCount >= 0 && mineCount < 10)
	{
		counter[0].setPosition(21, (row * 32));
		window.draw(counter[0]);
		counter[0].setPosition(42, (row * 32));
		window.draw(counter[0]);
		int index = mineCountS[0] - '0';
		counter[index].setPosition((21 * (3)), (row * 32));
		window.draw(counter[index]);
	}
	else if (mineCount > 9 && mineCount < 100)
	{
		counter[0].setPosition(21, (row * 32));
		window.draw(counter[0]);
		for (unsigned int i = 0; i < mineCountS.size(); i++)
		{
			int index = mineCountS[i] - '0';
			counter[index].setPosition((21 * (i + 2)), (row * 32));
			window.draw(counter[index]);
		}
	}
	else
	{
		for (unsigned int i = 0; i < mineCountS.size(); i++)
		{
			int index = mineCountS[i] - '0';
			counter[index].setPosition((21 * (i + 1)), (row * 32));
			window.draw(counter[index]);
		}
	}
}

void Board::setFace(int cond)
{
	if (cond == 0)
	{
		face.setTexture(TextureManager::GetTexture("face_happy"));
	}
	else if (cond == 1)
	{
		face.setTexture(TextureManager::GetTexture("face_win"));
	}
	else
	{
		face.setTexture(TextureManager::GetTexture("face_lose"));
	}
}

void Board::flagTile(int row, int col)
{
	if (!tiles[row][col]->checkReveal())
	{
		if (!tiles[row][col]->checkFlag())
		{
			mineCount--;
		}
		else
		{
			mineCount++;
		}
		tiles[row][col]->toggleFlag();
	}
}

void Board::revealTile(Tile*& tile)
{
	if (tile->checkMine() && !tile->checkFlag())
	{
		for (unsigned int i = 0; i < row; i++)
		{
			for (unsigned int j = 0; j < col; j++)
			{
				if (tiles[i][j]->checkMine())
				{
					tiles[i][j]->toggleReveal();
				}
			}
		}
		setFace(2);
		lose = 1;
	}
	else if (!tile->checkMine() && !tile->checkReveal() && !tile->checkFlag())
	{
		tile->toggleReveal();
		if (tile->adjacentBomb() == 0)
		{
			for (unsigned int i = 0; i < tile->adjacentTiles.size(); i++)
			{
				revealTile(tile->adjacentTiles[i]);
			}
		}
	}

}

void Board::reset()
{
	for (unsigned int i = 0; i < row; i++)
	{
		for (unsigned int j = 0; j < col; j++)
		{
			tiles[i][j]->reset();
		}
	}
	setFace(0);
	win = 0;
	lose = 0;
	mineCount = ogcount;
	//randomize board
	int add = 0;
	while (add < mineCount)
	{
		int randRow = Random::Int(0, row - 1);
		int randCol = Random::Int(0, col - 1);
		for (unsigned int i = 0; i < row; i++)
		{
			for (unsigned int j = 0; j < col; j++)
			{
				if ((i == randRow && j == randCol) && (tiles[i][j]->checkMine() == 0))
				{
					tiles[i][j]->toggleMine();
					add++;
				}
			}
		}
	}
}

void Board::loadTest(string& file)
{
	for (unsigned int i = 0; i < row; i++)
	{
		for (unsigned int j = 0; j < col; j++)
		{
			tiles[i][j]->reset();
		}
	}
	mineCount = 0;
	setFace(0);
	win = 0;
	lose = 0;
	ifstream infFile(file);
	if (infFile.is_open())
	{
		string line;
		for (unsigned int i = 0; i < row; i++)
		{
			getline(infFile, line);
			for (unsigned int j = 0; j < col; j++)
			{
				if (line[j] == '1')
				{
					tiles[i][j]->toggleMine();
					mineCount++;
				}
			}
		}

	}
}

void Board::Debug()
{
	for (unsigned int i = 0; i < row; i++)
	{
		for (unsigned int j = 0; j < col; j++)
		{
			tiles[i][j]->toggleDebug();
		}
	}
}

Tile* Board::tileAt(int row, int col)
{
	return tiles[row][col];
}

//Accessors
sf::Sprite Board::getSmile() { return face; }
sf::Sprite Board::getDebug() { return debug; }
sf::Sprite Board::getTest(int test)
{
	if (test == 1)
	{
		return test_1;
	}
	else if (test == 2)
	{
		return test_2;
	}
	else
	{
		return test_3;
	}
}
bool Board::checkLose() { return lose; }
bool Board::checkWin()
{
	int winc1 = 0;
	int winc2 = 0;
	for (unsigned int i = 0; i < row; i++)
	{
		for (unsigned int j = 0; j < col; j++)
		{
			if (tiles[i][j]->checkReveal() || tiles[i][j]->checkFlag())
			{
				winc1++;
			}
		
		}
	}
	if (winc1 == (row*col) - mineCount)
	{
		win = 1;
		setFace(1);
		for (unsigned int i = 0; i < row; i++)
		{
			for (unsigned int j = 0; j < col; j++)
			{
				if (!tiles[i][j]->checkFlag())
				{
					tiles[i][j]->toggleFlag();
				}
				if (tiles[i][j]->checkDebug())
				{
					tiles[i][j]->toggleDebug();
				}
			}
		}
		mineCount = 0;
	}
	return win;
}
