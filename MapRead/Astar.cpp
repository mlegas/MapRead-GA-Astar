// Astar.cpp
// http://en.wikipedia.org/wiki/A*
// Compiler: Dev-C++ 4.9.9.2
// FB - 201012256
#include <iostream>
#include <iomanip>
#include <cmath>
#include <queue>
#include "Astar.h"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Node.h"
#include "Maze.h"
#include "PathFind.h"

void Astar(sf::RenderWindow &_window)
{
	const int dir = 8; // number of possible directions to go at any position
					   // if dir==4
					   //static int dx[dir]={1, 0, -1, 0};
					   //static int dy[dir]={0, 1, 0, -1};
					   // if dir==8
	int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

	int x;
	int y;;
	int choice = 0;

	bool quitProgram = false;
	bool repeatProgram = true;

	Maze maze("map.txt");
	Grid grid(maze, _window.getSize().x, _window.getSize().y);

	while (!quitProgram && repeatProgram)
	{
		repeatProgram = false;
		x = maze.getStartX();
		y = maze.getStartY();

		std::cout << "Map Size (X,Y): " << maze.getX() << "," << maze.getY() << std::endl;
		std::cout << "Start: " << maze.getStartX() << "," << maze.getStartY() << std::endl;
		std::cout << "Finish: " << maze.getEndX() << "," << maze.getEndY() << std::endl;
		// get the route
		clock_t start = clock();
		std::vector<int> route = pathFind(maze);
		if (route.empty()) std::cout << "An empty route generated!" << std::endl;
		clock_t end = clock();
		double time_elapsed = double(end - start);
		std::cout << "Time to calculate the route (ms): " << time_elapsed << std::endl;
		std::cout << "Route:" << std::endl;

		// follow the route on the map and display it 
		if (route.size() > 0)
		{
			int j;

			for (int i = route.size() - 1; i >= 0; i--)
			{
				j = route.at(i);
				switch (j)
				{
				case 0:
				{
					std::cout << "Right ";
					break;
				}
				case 1:
				{
					std::cout << "Down-Right ";
					break;
				}
				case 2:
				{
					std::cout << "Down ";
					break;
				}
				case 3:
				{
					std::cout << "Down-Left ";
					break;
				}
				case 4:
				{
					std::cout << "Left ";
					break;
				}
				case 5:
				{
					std::cout << "Up-Left ";
					break;
				}
				case 6:
				{
					std::cout << "Up ";
					break;
				}
				case 7:
				{
					std::cout << "Up-Right ";
					break;
				}
				default:
				{
					break;
				}
				}

				x = x + dx[j];
				y = y + dy[j];
				if (x != maze.getEndX() || y != maze.getEndY())
				{
					grid.getTiles().at(y).at(x)->setFillColor(sf::Color(255, 255, 0));
				}
			}

			while (_window.isOpen() && !quitProgram && !repeatProgram)
			{
				sf::Event event;

				while (_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						_window.close();
					}
				}

				for (int i = 0; i < grid.getTiles().size(); i++)
				{
					for (int j = 0; j < grid.getTiles().at(i).size(); j++)
					{
						_window.draw(*(grid.getTiles().at(i).at(j)));
					}
				}

				_window.display();

				std::cout << "\n";

				bool correctChoice = false;
				while (!correctChoice)
				{
					std::cout << "Path was found!\n";
					std::cout << "0. Return to the main menu\n";
					std::cout << "1. Repeat the program\n";
					std::cin >> choice;
					switch (choice)
					{
					case 0:
					{
						correctChoice = true;
						repeatProgram = false;
						quitProgram = true;
						system("CLS");
						break;
					}
					case 1:
					{
						correctChoice = true;
						repeatProgram = true;
						system("CLS");
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
		}
		else
		{
			std::cout << "\n";

			bool correctChoice = false;
			while (!correctChoice)
			{
				std::cout << "Path was not found.\n";
				std::cout << "1. Repeat the program\n";
				std::cout << "0. Return to the main menu\n";
				std::cin >> choice;
				switch (choice)
				{
					case 0:
					{
						correctChoice = true;
						repeatProgram = false;
						quitProgram = true;
						system("CLS");
						break;
					}
					case 1:
					{
						correctChoice = true;
						repeatProgram = true;
						system("CLS");
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
	}
}