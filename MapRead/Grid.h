#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Maze;

class Grid
{
public:
	Grid(Maze &_maze, int _windowWidth, int _windowHeight);
	std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>> getTiles();
	~Grid();
private:
	std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>> m_tiles;
};

