#pragma once
#include<vector>
#include "SFML\Graphics.hpp"

extern int sizeX;
extern int sizeY;

class Rules
{
public:
	Rules();
	~Rules();

	void applyRules(int &neighbours, std::vector< std::vector<int> > &grid, std::vector< std::vector<int> > &nextgen, int i, int j);
	void performNextConwayIteration(std::vector< std::vector<int> > &grid, std::vector< std::vector<int> > &nextgen, int neighbours);
	void changeState(std::vector<std::vector<int> > &nextgen, std::vector<std::vector<sf::RectangleShape>> &rectangles, sf::RenderWindow *window);
	
private:
	static const auto offset = 1;
	
	
};

