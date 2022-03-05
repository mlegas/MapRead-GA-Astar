#pragma once
#include <SFML/Graphics.hpp>

class OptimalPath;
class Cycle;
class Maze;
class Grid;

bool Termination(OptimalPath &_optimalPath, Cycle &_cycle, Maze &_maze, Grid &_grid, sf::RenderWindow &_window);