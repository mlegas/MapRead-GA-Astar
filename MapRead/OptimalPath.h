#pragma once
#include <vector>
#include <memory>

class Cycle;
class Maze;
class Chromosome;

class OptimalPath
{
public:
	OptimalPath(int _population, int _chromosomeLength);
	std::shared_ptr<Chromosome> getChromosomePtr(int _location);
	void setChromosome(int _location, Chromosome &_chromosome);
	void searchForEnd(Maze &_maze, Cycle &_cycle);
	int getTimesEndFound();
	bool isSearchingForOptimalPath();
	bool isEndFound();
	bool noPathFound();
	bool getOutcome();
	void incrementInitialGenerationCount();
	bool isSearchingForInitialPath();
	int getSolution();
	void incrementOptimalGenerationCount();
	void resetOptimalGenerationCount();
	~OptimalPath();

private:
	bool m_searchingForInitialPath;
	int m_initialGenerationCount;
	bool m_endFoundOnce;
	bool m_endFound;
	bool m_noPathFound;
	int m_optimalGenerationCount;
	int m_timesEndFound;
	int m_lastChromosomeLength;
	int m_chromosomePosition;
	bool m_searchingForBetterPath;
	bool m_chromosomeLengthTooLow;
	int m_solution;

	void goThroughTheMaze(Maze &_maze, Cycle &_cycle);

	std::vector<std::shared_ptr<Chromosome>> m_optimalRouteChromosomes;
};

