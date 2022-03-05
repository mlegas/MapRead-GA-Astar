#include "OptimalPath.h"
#include <iostream>
#include <vector>

#include "Maze.h"
#include "Cycle.h"
#include "Chromosome.h"

OptimalPath::OptimalPath(int _population, int _chromosomeLength)
{
	for (int i = 0; i < _population; i++)
	{
		std::shared_ptr<Chromosome> chromosome = std::make_shared<Chromosome>(_chromosomeLength);
		m_optimalRouteChromosomes.push_back(chromosome);
	}
	m_endFound = false;
	m_noPathFound = false;
	m_endFoundOnce = false;
	m_searchingForInitialPath = true;
	m_timesEndFound = 0;
	m_searchingForBetterPath = false;
	m_chromosomeLengthTooLow = false;
	m_optimalGenerationCount = 0;
	m_lastChromosomeLength = _chromosomeLength;
	m_chromosomePosition = 0;
	m_solution = 0;
}

std::shared_ptr<Chromosome> OptimalPath::getChromosomePtr(int _location)
{
	return m_optimalRouteChromosomes.at(_location);
}

void OptimalPath::setChromosome(int _location, Chromosome &_chromosome)
{
	*m_optimalRouteChromosomes.at(_location) = _chromosome;
}

bool OptimalPath::isEndFound()
{
	return m_endFound;
}

bool OptimalPath::noPathFound()
{
	return m_noPathFound;
}

void OptimalPath::incrementOptimalGenerationCount()
{
	m_optimalGenerationCount++;
}

void OptimalPath::resetOptimalGenerationCount()
{
	m_optimalGenerationCount = 0;
}

int OptimalPath::getTimesEndFound()
{
	return m_timesEndFound;
}

void OptimalPath::incrementInitialGenerationCount()
{
	m_initialGenerationCount++;
}

bool OptimalPath::isSearchingForInitialPath()
{
	return m_searchingForInitialPath;
}

bool OptimalPath::isSearchingForOptimalPath()
{
	return m_searchingForBetterPath;
}


void OptimalPath::searchForEnd(Maze &_maze, Cycle &_cycle)
{
	m_endFound = false;
	goThroughTheMaze(_maze, _cycle);

	if (m_endFound)
	{
		m_searchingForInitialPath = false;
		m_timesEndFound++;

		if (_cycle.getChromosomeLength() == 1)
		{
			m_endFoundOnce = true;
			m_searchingForBetterPath = false;
			m_chromosomeLengthTooLow = true;
		}

		else
		{
			m_searchingForBetterPath = true;
			m_endFoundOnce = true;
			m_endFound = false;
			m_lastChromosomeLength = _cycle.getChromosomeLength();
			m_optimalGenerationCount = 0;

			for (int i = 0; i < _cycle.getPopulation(); i++)
			{
				m_optimalRouteChromosomes.at(i)->resize(m_lastChromosomeLength);

				for (int j = 0; j < _cycle.getChromosomeLength(); j++)
				{
					m_optimalRouteChromosomes.at(i)->setMove(j, _cycle.getChromosomePtr(i)->getMove(j));
				}

				_cycle.getChromosomePtr(i)->resize(m_chromosomePosition);
			}

			_cycle.setChromosomeLength(m_chromosomePosition);
		}
	}
	else if (!m_endFound && m_initialGenerationCount > 30000) // if no initial path found for 30000 generations - return that there is no path
	{
		m_noPathFound = true;
	}

	else if (m_optimalGenerationCount >= 250) // search if there is a better path for 250 generations without an improvement of fitness in any chromosome
	{
		if (!m_searchingForBetterPath)
		{
			m_noPathFound = true;
		}

		else if (m_searchingForBetterPath)
		{
			if (m_endFoundOnce)
			{
				m_endFound = true;
			}

			else
			{
				m_noPathFound = true;
			}

			if (m_lastChromosomeLength != _cycle.getInitialChromosomeLength())
			{
				_cycle.setChromosomeLength(m_lastChromosomeLength);

				for (int i = 0; i < _cycle.getPopulation(); i++)
				{
					_cycle.getChromosomePtr(i)->resize(m_lastChromosomeLength);
					_cycle.setChromosome(i, *m_optimalRouteChromosomes.at(i));
				}
			}
		}
	}

}

int OptimalPath::getSolution()
{
	return m_solution;
}

bool OptimalPath::getOutcome()
{
	if (m_endFoundOnce == true && m_noPathFound == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void OptimalPath::goThroughTheMaze(Maze &_maze, Cycle &_cycle)
{
	int currentYPos;
	int currentXPos;

	for (int i = 0; i < _cycle.getPopulation(); i++)
	{
		currentYPos = _maze.getStartY();
		currentXPos = _maze.getStartX();

		for (int chromosomePosition = 0; chromosomePosition < _cycle.getChromosomeLength(); chromosomePosition++)
		{
			switch (_cycle.getChromosomePtr(i)->getMove(chromosomePosition))
			{
			case 0:
			{
				if (currentYPos > 0) // up
				{
					if (_maze.getMap().at(currentYPos - 1).at(currentXPos) != 1)
					{
						--currentYPos;
					}
				}
				break;
			}

			case 1:
			{
				if (currentXPos < _maze.getX() - 1) // right
				{
					if (_maze.getMap().at(currentYPos).at(currentXPos + 1) != 1)
					{
						++currentXPos;
					}
				}
				break;
			}

			case 2:
			{
				if (currentYPos < _maze.getY() - 1) // down
				{
					if (_maze.getMap().at(currentYPos + 1).at(currentXPos) != 1)
					{
						++currentYPos;
					}
				}
				break;
			}

			case 3:
			{
				if (currentXPos > 0) // left
				{
					if (_maze.getMap().at(currentYPos).at(currentXPos - 1) != 1)
					{
						--currentXPos;
					}
				}
				break;
			}

			case 4:
			{
				if (currentYPos > 0 && currentXPos > 0) // up-left
				{
					if (_maze.getMap().at(currentYPos - 1).at(currentXPos - 1) != 1)
					{
						--currentXPos;
						--currentYPos;
					}
				}
				break;
			}

			case 5:
			{
				if (currentYPos > 0 && currentXPos < _maze.getX() - 1) // up-right
				{
					if (_maze.getMap().at(currentYPos - 1).at(currentXPos + 1) != 1)
					{
						++currentXPos;
						--currentYPos;
					}
				}
				break;
			}

			case 6:
			{
				if (currentYPos < _maze.getY() - 1 && currentXPos < _maze.getX() - 1) // down-right
				{
					if (_maze.getMap().at(currentYPos + 1).at(currentXPos + 1) != 1)
					{
						++currentXPos;
						++currentYPos;
					}
				}
				break;
			}

			case 7:
			{
				if (currentYPos < _maze.getY() - 1 && currentXPos > 0) // down-left
				{
					if (_maze.getMap().at(currentYPos + 1).at(currentXPos - 1) != 1)
					{
						--currentXPos;
						++currentYPos;
					}
				}
				break;
			}

			default:
			{
				std::cout << "Something went horribly wrong while traversing chromosome number " << i << "." << std::endl;
				std::cout << "Quite possibly an incorrect value has been generated for one of its moves." << std::endl;
				std::cout << "Check the constructor of chromosome.cpp" << std::endl;
				break;
			}
			}

			if (currentYPos == _maze.getEndY() && currentXPos == _maze.getEndX())
			{
				m_chromosomePosition = chromosomePosition;
				m_solution = i;
				m_endFound = true;
			}
		}
		_cycle.getChromosomePtr(i)->calculateFitness(_maze.getEndX(), _maze.getEndY(), currentXPos, currentYPos);
	}
}

OptimalPath::~OptimalPath()
{
}
