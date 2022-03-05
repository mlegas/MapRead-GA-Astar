#include "Maze.h"
#include <fstream>

Maze::Maze(std::string _filename)
{
	std::fstream mapFile;
	mapFile.open(_filename, std::fstream::in);

	std::vector<int> numbers;

	int temp;

	while (!mapFile.eof())
	{
		mapFile >> temp;
		numbers.push_back(temp);
	}

	mapFile.close();

	m_x = numbers.at(0);
	m_y = numbers.at(1);

	m_maze = std::vector<std::vector<int>>(m_y, std::vector<int>(m_x, 0));

	int k = 2;

	for (int i = 0; i < m_y; i++)
	{
		for (int j = 0; j < m_x; j++)
		{
			m_maze.at(i).at(j) = numbers.at(k);

			if (m_maze.at(i).at(j) == 2)
			{
				m_startY = i;
				m_startX = j;
			}

			else if (m_maze.at(i).at(j) == 3)
			{
				m_endY = i;
				m_endX = j;
			}

			k++;
		}
	}
}

Maze::~Maze()
{
}

std::vector<std::vector<int>> Maze::getMap()
{
	return m_maze;
}

int Maze::getX()
{
	return m_x;
}

int Maze::getY()
{
	return m_y;
}

int Maze::getStartX()
{
	return m_startX;
}

int Maze::getStartY()
{
	return m_startY;
}

int Maze::getEndX()
{
	return m_endX;
}

int Maze::getEndY()
{
	return m_endY;
}
