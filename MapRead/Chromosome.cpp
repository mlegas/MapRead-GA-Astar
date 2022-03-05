#include "Chromosome.h"
#include <memory>
#include <random>
#include "Maze.h"

Chromosome::Chromosome(int _chromosomeLength)
{
	std::random_device generator;
	std::uniform_int_distribution<int> distribution(0, 7);

	for (int i = 0; i < _chromosomeLength; i++)
	{
		std::shared_ptr<int> move = std::make_shared<int>();
		*move = distribution(generator);
		m_moves.push_back(move);
	}

	m_fitness = std::make_shared<float>(0.0f);
}

Chromosome::Chromosome(int _initialization[])
{
	for (int i = 0; i < _initialization[0]; i++)
	{
		std::shared_ptr<int> move = std::make_shared<int>();
		*move = _initialization[1];

		m_moves.push_back(move);
	}

	m_fitness = std::make_shared<float>(0.0f);
}

void Chromosome::calculateFitness(int _endX, int _endY, int _currentXPos, int _currentYPos)
{
	float deltaX, deltaY;

	deltaX = abs(_endX - _currentXPos);
	deltaY = abs(_endY - _currentYPos);

	*m_fitness = 1 / (deltaX + deltaY + 1);
}

int Chromosome::getMove(int _location)
{
	return *m_moves.at(_location);
}

void Chromosome::setMove(int _location, int _move)
{
	*m_moves.at(_location) = _move;
}

float Chromosome::getFitness()
{
	return *m_fitness;
}

void Chromosome::resize(int _chromosomeLength)
{
	m_moves.resize(_chromosomeLength);
}