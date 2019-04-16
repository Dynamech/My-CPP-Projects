#include "Menu.h"

///This is the class for the main menu displaying the 3 options.

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
	//handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Load numbers from a file");
	menu[0].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setString("Generate random numbers");
	menu[1].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Black);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

///draw the menu in the windows loop
void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

///move the menu cursor up
void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Cyan);
	}
}

///move the cursor down
void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Cyan);
	}
}