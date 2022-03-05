#include "Chromosome.h"
#include "Cycle.h"
#include <random>
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Chromosome>> Crossover(Cycle &_cycle, std::random_device &_generator, std::uniform_real_distribution<float> &_distribution, std::vector<int> &_selectedChromosomes)
{
	int allocator[2] = { _cycle.getChromosomeLength(), 0 };
	
	std::vector<std::shared_ptr<Chromosome>> crossoverChromosomes;
	for (int i = 0; i < _cycle.getPopulation(); i++)
	{
		std::shared_ptr<Chromosome> chromosome = std::make_shared<Chromosome>(allocator);
		crossoverChromosomes.push_back(chromosome);
	}
	
	float crossoverRate = 0.7f;
	float uniformCrossoverRate = 0.5f;

	for (int i = 0; i < _cycle.getPopulation(); i = i + 2)
	{
		double crossover = _distribution(_generator);

		if (crossover <= crossoverRate)
		{
			for (int j = 0; j < _cycle.getChromosomeLength(); j++)
			{
				double uniformCrossover = _distribution(_generator);

				if (uniformCrossover <= uniformCrossoverRate)
				{
					crossoverChromosomes.at(i)->setMove(j, _cycle.getChromosomePtr(_selectedChromosomes.at(i + 1))->getMove(j));
					crossoverChromosomes.at(i + 1)->setMove(j, _cycle.getChromosomePtr(_selectedChromosomes.at(i))->getMove(j));
				}

				else
				{
					crossoverChromosomes.at(i)->setMove(j, _cycle.getChromosomePtr(_selectedChromosomes.at(i))->getMove(j));
					crossoverChromosomes.at(i + 1)->setMove(j, _cycle.getChromosomePtr(_selectedChromosomes.at(i + 1))->getMove(j));
				}
			}
		}

		else
		{
			for (int j = 0; j < _cycle.getChromosomeLength(); j++)
			{
				crossoverChromosomes.at(i)->setMove(j, _cycle.getChromosomePtr(_selectedChromosomes.at(i))->getMove(j));
				crossoverChromosomes.at(i + 1)->setMove(j, _cycle.getChromosomePtr(_selectedChromosomes.at(i + 1))->getMove(j));
			}
		}
	}

	return crossoverChromosomes;
}