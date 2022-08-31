#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <random>
#include <ctime>
#include <vector>
#include "TextureManager.h"
#include "Random.h"
using namespace std;

//function initialization
void readConfig(vector<int>& config);

//function definition
void readConfig(vector<int>& config)
{

	ifstream inFile("boards/config.cfg");
	string colNum, rowNum, mineCount;
	if (inFile.is_open())
	{
		getline(inFile, colNum);
		config.push_back(stoi(colNum));
		getline(inFile, rowNum);
		config.push_back(stoi(rowNum));
		getline(inFile, mineCount);
		config.push_back(stoi(mineCount));
	}

}
