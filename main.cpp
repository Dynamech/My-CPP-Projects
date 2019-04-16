#include <SFML\Graphics.hpp>
#include "Menu.h"
#include "Rules.h"
#include "Initialize.h"

int sizeX;
int sizeY;

int main()
{
	
	int neighbours = 0;
	bool running = 0;
	std::ifstream boardFile("boardfile.txt");
	boardFile >> sizeX;
	boardFile >> sizeY;
	std::vector<std::vector<int>>grid(sizeY, std::vector<int>(sizeX));
	std::vector<std::vector<int>>nextGen(sizeY, std::vector<int>(sizeX));
	std::vector<std::vector<sf::RectangleShape>>rectangles(sizeY, std::vector<sf::RectangleShape>(sizeX));
	sf::RenderWindow window(sf::VideoMode(600, 600), "Conway's Game of Life 2.1");
	Menu menu(window.getSize().x, window.getSize().y);
	Initialize initialize;
	Rules rules;
	
	for (int i = 0; i<sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			rectangles[i][j].setOrigin(-50,-50);
			rectangles[i][j].setFillColor(sf::Color::Black);
		}
	}

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					if (running == 0)
					{
						switch (menu.GetPressedItem())
						{
						case 0:
							
							initialize.loadFile(boardFile, grid);
							std::cout << "keyPressed";
							running = 1;
							break;
						case 1:

							initialize.generateRandomNumbers(grid);
							running = 1;
							break;
						case 2:
							window.close();
							break;
						}

						break;
					}
				case::sf::Keyboard::Escape:
					window.close();
					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}
		
		window.clear(sf::Color::White);
		if (running == 0)
		{
			menu.draw(window);
		}
		else
		{
			rules.performNextConwayIteration(grid, nextGen, neighbours);
			rules.changeState(nextGen, rectangles, &window);
		}
		window.display();
	}

	return 0;
}

