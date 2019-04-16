#include "Rules.h"


Rules::Rules()
{
}


Rules::~Rules()
{
}

///Conway's game of life standard ruleset.

void Rules::applyRules(int & neighbours, std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& nextgen, int i, int j)
{
	if (grid[i][j] == 1)
	{
		if (neighbours < 2)
			nextgen[i][j] = 0;
		else if (neighbours == 2 || neighbours == 3)
			nextgen[i][j] = 1;
		else if (neighbours > 3)
			nextgen[i][j] = 0;
	}
	else if (grid[i][j] == 0)
	{
		if (neighbours == 3)
			nextgen[i][j] = 1;
		else
			nextgen[i][j] = 0;
	}
}

///This function loops through the board and iterates the neighbours variable if the said conditions are met.

void Rules::performNextConwayIteration(std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& nextgen, int neighbours)
{
	for (int i = offset; i < sizeY - offset; i++)
	{

		for (int j = 1; j < sizeX - 1; j++)
		{
			if (grid[i - offset][j - offset] == 1)neighbours++;
			if (grid[i - offset][j] == 1)neighbours++;
			if (grid[i - offset][j + offset] == 1)neighbours++;
			if (grid[i][j - offset] == 1)neighbours++;
			if (grid[i][j + offset] == 1)neighbours++;
			if (grid[i + offset][j - offset] == 1)neighbours++;
			if (grid[i + offset][j] == 1)neighbours++;
			if (grid[i + offset][j + offset] == 1)neighbours++;
			applyRules(neighbours, grid, nextgen, i, j);
			neighbours = 0;
		}
	}

	std::swap(grid, nextgen);
}

void Rules::changeState(std::vector<std::vector<int>>& nextgen, std::vector<std::vector<sf::RectangleShape>>& rectangles, sf::RenderWindow * window)
{
	for (int i = 0; i<sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			rectangles[i][j].setSize(sf::Vector2f(10, 10));
			rectangles[i][j].setPosition(i * 10, j * 10);
			rectangles[i][j].setFillColor(sf::Color::Cyan);
			rectangles[i][j].setOutlineColor(sf::Color::Black);
			rectangles[i][j].setOutlineThickness(1);
			if (nextgen[i][j] == 1)
				rectangles[i][j].setFillColor(sf::Color::Cyan);
			else if (nextgen[i][j] == 0)
			{
				rectangles[i][j].setFillColor(sf::Color::White);
			}
			window->draw(rectangles[i][j]);

		}

	}
}
