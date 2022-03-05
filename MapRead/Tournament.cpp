#include <vector>
#include <random>
#include "Cycle.h"
#include "Chromosome.h"

std::vector<int> Tournament(Cycle &_cycle, std::random_device &_generator)
{
	int tournamentSize = 3;
	int bestFitnessChromosome = 0;
	
	std::uniform_int_distribution<int> tournament(0, _cycle.getPopulation() - 1);

	std::vector<int> selectedChromosomes(_cycle.getPopulation(), 0);
	std::vector<int> tournamentChrosomomes(tournamentSize, 0);

	for (int i = 0, k = 0; i < _cycle.getPopulation(); i++, k++)
	{
		for (int j = 0; j < tournamentSize; j++)
		{
			int random = tournament(_generator);
			tournamentChrosomomes.at(j) = random;
		}

		float bestFitness = 0.0f;

		for (int j = 0; j < tournamentSize; j++)
		{
			if (_cycle.getChromosomePtr(tournamentChrosomomes.at(j))->getFitness() > bestFitness)
			{
				bestFitness = _cycle.getChromosomePtr(tournamentChrosomomes.at(j))->getFitness();
				bestFitnessChromosome = tournamentChrosomomes.at(j);
			}
		}

		selectedChromosomes.at(k) = bestFitnessChromosome;
	}

	return selectedChromosomes;
}