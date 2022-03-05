#include <vector>
#include <memory>
#include <random>
#include "Cycle.h"
#include "Chromosome.h"

void Mutation(std::vector<std::shared_ptr<Chromosome>> &_offspring, Cycle &_cycle, std::uniform_real_distribution<float> &_distribution, std::random_device &_generator)
{
	float mutationRate = 0.1f;

	std::uniform_int_distribution<int> mutation(0, 7);

	for (int i = 0; i < _cycle.getPopulation(); i++)
	{
		for (int j = 0; j < _cycle.getChromosomeLength(); j++)
		{
			float random = _distribution(_generator);

			if (random <= mutationRate)
			{
				_offspring.at(i)->setMove(j, mutation(_generator));
			}
		}
	}
}