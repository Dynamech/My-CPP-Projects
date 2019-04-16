#include "Initialize.h"

///This class is used to initialize the board letting the user choose if he wants to load the numbers from a file or generate them randomly.

Initialize::Initialize()
{

}


Initialize::~Initialize()
{

}

///loadFile is executed if the user chooses to load the values from a file.

void Initialize::loadFile(std::ifstream &board_file, std::vector< std::vector<int> > &grid)
{
	while (!board_file.eof())
	{

		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j<sizeX; j++)
			{
				board_file >> grid[i][j];
			}
		}

	}
	board_file.close();
}

///Random numbers generator.

void Initialize::generateRandomNumbers(std::vector< std::vector<int> > &grid)
{
	srand(time(NULL));

	for (int i = 0; i < sizeY; i++)
	{
		{
			for (int j = 0; j < sizeX; j++)
			{
				grid[i][j] = rand() % rand_number_range;
				std::cout << grid[i][j];
			}
			std::cout << std::endl;
		}
	}
}