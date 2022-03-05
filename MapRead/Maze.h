#pragma once
#include <vector>

class Maze
{
public:
	Maze(std::string _filename);
	~Maze();

	int getX();
	int getY();
	int getStartX();
	int getStartY();
	int getEndX();
	int getEndY();

	std::vector<std::vector<int>> getMap();

private:
	std::vector<std::vector<int>> m_maze;

	int m_x;
	int m_y;
	int m_startX;
	int m_startY;
	int m_endX;
	int m_endY;
};




