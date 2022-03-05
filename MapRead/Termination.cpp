#include <SFML\Graphics.hpp>
#include "Crossover.h"
#include "Chromosome.h"
#include "Cycle.h"
#include "Mutation.h"
#include "Tournament.h"
#include "OptimalPath.h"
#include "Grid.h"
#include "Maze.h"
#include <iostream>
#include <fstream>
#include <random>
#include <memory>
#include <vector>

bool Termination(OptimalPath &_optimalPath, Cycle &_cycle, Maze &_maze, Grid &_grid, sf::RenderWindow &_window)
{
	if (_optimalPath.getOutcome())
	{
		int choice;

		std::cout << "Termination criterion satisfied!" << std::endl;
		std::cout << "Chromosome number: " << _optimalPath.getSolution() << std::endl;
		std::cout << "Generation: " << _cycle.getCurrentGeneration() << std::endl;
		std::cout << "Chromosome length: " << _cycle.getChromosomeLength() << std::endl;
		std::cout << "A correct solution has been found in this many generations: " << _optimalPath.getTimesEndFound() << std::endl;
		std::cout << "The path: ";

		int tempY = _maze.getStartY();
		int tempX = _maze.getStartX();

		for (int i = 0; i < _cycle.getChromosomeLength(); i++)
		{
			bool movementMade = false;

			switch (_cycle.getChromosomePtr(_optimalPath.getSolution())->getMove(i))
			{
				case 0:
				{
					std::cout << "Up ";
					if (tempY > 0)
					{
						if (_maze.getMap().at(tempY - 1).at(tempX) != 1)
						{
							movementMade = true;
							--tempY;
						}
					}
					break;
				}
				case 1:
				{
					std::cout << "Right ";
					if (tempX < _maze.getX() - 1)
					{
						if (_maze.getMap().at(tempY).at(tempX + 1) != 1)
						{
							movementMade = true;
							++tempX;
						}
					}
					break;
				}
				case 2:
				{
					std::cout << "Down ";
					if (tempY < _maze.getY() - 1)
					{
						if (_maze.getMap().at(tempY + 1).at(tempX) != 1)
						{
							movementMade = true;
							++tempY;
						}
					}
					break;
				}
				case 3:
				{
					std::cout << "Left ";
					if (tempX > 0)
					{
						if (_maze.getMap().at(tempY).at(tempX - 1) != 1)
						{
							movementMade = true;
							--tempX;
						}
					}
					break;
				}
				case 4:
				{
					std::cout << "Up-Left ";
					if (tempY > 0 && tempX > 0)
					{
						if (_maze.getMap().at(tempY - 1).at(tempX - 1) != 1)
						{
							movementMade = true;
							--tempX;
							--tempY;
						}
					}
					break;
				}
				case 5:
				{
					std::cout << "Up-Right ";
					if (tempY > 0 && tempX < _maze.getX() - 1)
					{
						if (_maze.getMap().at(tempY - 1).at(tempX + 1) != 1)
						{
							movementMade = true;
							++tempX;
							--tempY;
						}
					}
					break;
				}
				case 6:
				{
					std::cout << "Down-Right ";
					if (tempY < _maze.getY() - 1 && tempX < _maze.getX() - 1)
					{
						if (_maze.getMap().at(tempY + 1).at(tempX + 1) != 1)
						{
							movementMade = true;
							++tempX;
							++tempY;
						}
					}
					break;
				}
				case 7:
				{
					std::cout << "Down-Left ";
					if (tempY < _maze.getY() - 1 && tempX > 0)
					{
						if (_maze.getMap().at(tempY + 1).at(tempX - 1) != 1)
						{
							movementMade = true;
							--tempX;
							++tempY;
						}
					}
					break;
				}
				default:
				{
					break;
				}
			}

			if (movementMade && (tempY != _maze.getEndY() || tempX != _maze.getEndX()))
			{
				_grid.getTiles().at(tempY).at(tempX)->setFillColor(sf::Color(255, 255, 0));
			}
		}

		std::cout << "\n\n";

		while (_window.isOpen())
		{
			sf::Event event;

			while (_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					_window.close();
				}
			}

			for (int i = 0; i < _grid.getTiles().size(); i++)
			{
				for (int j = 0; j < _grid.getTiles().at(i).size(); j++)
				{
					_window.draw(*(_grid.getTiles().at(i).at(j)));
				}
			}
				bool correctChoice = false;
				while (!correctChoice)
				{
					_window.display();
					std::cout << "0. Return to the main menu\n";
					std::cout << "1. Repeat the program\n";
					std::cin >> choice;
					switch (choice)
					{
						case 0:
						{
							system("CLS");
							return true;
							break;
						}
						case 1:
						{
							correctChoice = true;
							system("CLS");
							return false;
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

	else if (!_optimalPath.getOutcome())
	{
		char choice;

		std::cout << "Termination criterion failed.\n";
		std::cout << "The Genetic Algorithm could not find the path.\n\n";
		std::cout << "This could be due to two reasons:\n\n";
		std::cout << "1. The end position is blocked by obstacles in such a way that it is unaccesible by any means.\n";
		std::cout << "2. The search for an initial, any possible path went over an optimal time limit.\n\n";
		bool correctChoice = false;

			while (!correctChoice)
			{
				std::cout << "Would you like to try again? [Y/N]\n";
				std::cin >> choice;

				switch (choice)
				{
					case 'Y':
					case 'y':
					{
						correctChoice = true;
						system("CLS");
						return false;
						break;
					}
					case 'N':
					case 'n':
					{
						correctChoice = true;
						return true;
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