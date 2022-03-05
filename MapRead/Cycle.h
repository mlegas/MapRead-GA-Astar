#pragma once
#include <vector>
#include <memory>

class Chromosome;

class Cycle
{
public:
	Cycle(int _x, int _y, int _population);
	~Cycle();

	std::shared_ptr<Chromosome> getChromosomePtr(int _location);
	void setChromosome(int _location, Chromosome &_chromosome);
	float getGenBestFitness();
	void setGenBestFitness(float _fitness);
	int getInitialChromosomeLength();
	int getChromosomeLength();
	void setChromosomeLength(int _chromosomeLength);
	int getPopulation();
	int getCurrentGeneration();
	void incrementGeneration();

private:
	std::vector<std::shared_ptr<Chromosome>> m_chromosomes;
	int m_chromosomeLength;
	int m_initialChromosomeLength;
	int m_population;
	float m_genBestFitness;
	int m_currentGeneration;
	void calculateChromosomeLength(int _x, int _y);
};

