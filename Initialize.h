#pragma once
#include <iostream>
#include<vector>
#include<ctime>
#include<random>
#include<fstream>

extern int sizeX;
extern int sizeY;

class Initialize
{
public:
	Initialize();
	~Initialize();

	void loadFile(std::ifstream &board_file, std::vector< std::vector<int> > &grid);
	void generateRandomNumbers(std::vector< std::vector<int> > &grid);
	
private:
	const int rand_number_range = 2;
};

