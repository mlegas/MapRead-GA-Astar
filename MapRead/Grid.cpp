#include "Grid.h"
#include "Maze.h"
#include <memory>


Grid::Grid(Maze &_maze, int _windowWidth, int _windowHeight)
{
	int tileWidth = _windowWidth / _maze.getX();
	int tileHeight = _windowHeight / _maze.getY();

	std::vector<std::shared_ptr<sf::RectangleShape>> tempVector;

	for (int i = 0; i < _maze.getY(); i++)
	{
		for (int j = 0; j < _maze.getX(); j++)
		{
			std::shared_ptr<sf::RectangleShape> tile = std::make_shared<sf::RectangleShape>(sf::Vector2f(tileWidth, tileHeight));
			tile->move(tileWidth * j, tileHeight * i);

			switch (_maze.getMap().at(i).at(j))
			{
			case 0:
				tile->setFillColor(sf::Color(255, 255, 255));
				break;
			case 1:
				tile->setFillColor(sf::Color(0, 0, 0));
				break;
			case 2:
				tile->setFillColor(sf::Color(0, 255, 0));
				break;
			case 3:
				tile->setFillColor(sf::Color(0, 0, 255));
				break;
			default:
				break;
			}

			tile->setOutlineThickness(5);
			tile->setOutlineColor(sf::Color(0, 0, 0));
			tempVector.push_back(tile);
		}
		m_tiles.push_back(tempVector);
		tempVector.clear();
	}
}

std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>> Grid::getTiles()
{
	return m_tiles;
}

Grid::~Grid()
{
}
