#include "Cycle.h"
#include "Chromosome.h"
#include <vector>
#include <memory>


Cycle::Cycle(int _x, int _y, int _population)
{
	calculateChromosomeLength(_x, _y);
	m_population = _population;
	m_initialChromosomeLength = m_chromosomeLength;

	for (int i = 0; i < m_population; i++)
	{
		std::shared_ptr<Chromosome> chromosome = std::make_shared<Chromosome>(m_chromosomeLength);
		m_chromosomes.push_back(chromosome);
	}
}
int Cycle::getChromosomeLength()
{
	return m_chromosomeLength;
}

int Cycle::getCurrentGeneration()
{
	return m_currentGeneration;
}

void Cycle::setChromosomeLength(int _chromosomeLength)
{
	m_chromosomeLength = _chromosomeLength;
}

float Cycle::getGenBestFitness()
{
	return m_genBestFitness;
}

void Cycle::setGenBestFitness(float _fitness)
{
	m_genBestFitness = _fitness;
}

int Cycle::getPopulation()
{
	return m_population;
}

int Cycle::getInitialChromosomeLength()
{
	return m_initialChromosomeLength;
}

void Cycle::incrementGeneration()
{
	m_currentGeneration++;
}

void Cycle::calculateChromosomeLength(int _x, int _y)
{
	int higher = 0, smaller = 0;

	if (_x >= _y)
	{
		higher = _x;
		smaller = _y;
	}

	else if (_y > _x)
	{
		higher = _y;
		smaller = _x;
	}

	if (smaller == 1)
	{
		m_chromosomeLength = higher - 1;
	}

	else
	{
		m_chromosomeLength = (_x * _y) - ((smaller - 2) * (higher / 2));
	}
}

std::shared_ptr<Chromosome> Cycle::getChromosomePtr(int _location)
{
	return m_chromosomes.at(_location);
}

void Cycle::setChromosome(int _location, Chromosome &_chromosome)
{
	*m_chromosomes.at(_location) = _chromosome;
}

Cycle::~Cycle()
{
}
