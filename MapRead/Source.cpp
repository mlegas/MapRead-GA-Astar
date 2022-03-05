#include <SFML/Graphics.hpp>
#include "Astar.h"
#include "GeneticAlgorithm.h"
#include <iostream>

int main()
{
	int windowWidth = 800;
	int windowHeight = 800;

	bool quitMenu = false;
	int choice;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "AI Programming");
	window.setPosition(sf::Vector2i(310, 10));

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		while (!quitMenu)
		{
			bool correctChoice = false;
			while (!correctChoice)
			{
				std::cout << "Choose what would you like to view:\n";
				std::cout << "1. Genetic Algorithm\n";
				std::cout << "2. A* algorithm\n";
				std::cout << "0. Quit\n";

				std::cin >> choice;
				switch (choice)
				{
					case 1:
					{
						correctChoice = true;
						system("CLS");
						GeneticAlgorithm(window);
						break;
					}
					case 2:
					{
						correctChoice = true;
						system("CLS");
						Astar(window);
						break;
					}
					case 0:
					{
						correctChoice = true;
						quitMenu = true;
						window.close();
						break;
					}
					default:
					{
						system("CLS");
						std::cout << "Incorrect input, please try again.\n\n";
						break;
					}
				}
			}
		}
		window.display();
	}

	return 0;
}