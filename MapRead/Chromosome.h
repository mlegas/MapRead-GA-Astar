#pragma once
#include <vector>
#include <memory>

class Maze;

class Chromosome
{
public:
	Chromosome(int _chromosomeLength);
	Chromosome(int _initialization[]);
	
	void calculateFitness(int _endX, int _endY, int _currentXPos, int _currentYPos);
	void resize(int _chromosomeLength);
	int getMove(int _location);
	void setMove(int _location, int _move);
	float getFitness();

private:
	std::shared_ptr<float> m_fitness;
	std::vector<std::shared_ptr<int>> m_moves;
};