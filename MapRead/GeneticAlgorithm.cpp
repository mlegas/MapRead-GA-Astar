#include <SFML\Graphics.hpp>
#include "Crossover.h"
#include "Chromosome.h"
#include "Cycle.h"
#include "Mutation.h"
#include "Tournament.h"
#include "Termination.h"
#include "OptimalPath.h"
#include "Grid.h"
#include "Maze.h"
#include <iostream>
#include <random>
#include <memory>
#include <vector>

void GeneticAlgorithm(sf::RenderWindow &_window)
{
	int population = 20;
	bool quitProgram = false;
	std::random_device generator;
	std::uniform_real_distribution<float> distribution(0, 1);

	while (!quitProgram)
	{

	Maze maze("map.txt"); // initialize the map file
	Grid grid(maze, _window.getSize().x, _window.getSize().y); // initialize the 2D grid
	Cycle cycle(maze.getX(), maze.getY(), population); // initialize a cycle of the current generation
	OptimalPath optimalPath(cycle.getPopulation(), cycle.getChromosomeLength()); // initialize the optimal path search

	float searchForBetterFitness = 0.0f;

	bool betterFitnessFound = false;
	
	clock_t start = clock();
	
	while (!optimalPath.isEndFound() && !optimalPath.noPathFound())
	{
		optimalPath.searchForEnd(maze, cycle);

		if (!optimalPath.isEndFound() && !optimalPath.noPathFound())
		{
			betterFitnessFound = false;

			std::vector<int> selectedChromosomes = Tournament(cycle, generator);
			std::vector<std::shared_ptr<Chromosome>> offspring = Crossover(cycle, generator, distribution, selectedChromosomes);
			Mutation(offspring, cycle, distribution, generator);

			for (int i = 0; i < cycle.getPopulation(); i++)
			{
				for (int j = 0; j < cycle.getChromosomeLength(); j++)
				{
					cycle.getChromosomePtr(i)->setMove(j, offspring.at(i)->getMove(j)); // move offspring to current gen
				}

				searchForBetterFitness = cycle.getChromosomePtr(i)->getFitness();

				if (searchForBetterFitness > cycle.getGenBestFitness())
				{
					cycle.setGenBestFitness(searchForBetterFitness);
					optimalPath.resetOptimalGenerationCount();
					betterFitnessFound = true;
				}
			}

			if (!betterFitnessFound)
			{
				if (optimalPath.isSearchingForOptimalPath())
				{
					optimalPath.incrementOptimalGenerationCount();
				}
				else if (optimalPath.isSearchingForInitialPath())
				{
					optimalPath.incrementInitialGenerationCount();
				}
			}
			else
			{
				betterFitnessFound = false;
			}

			cycle.incrementGeneration();
		}
	}
	clock_t end = clock();
	double time_elapsed = double(end - start);
	std::cout << "Time to calculate the route (ms): " << time_elapsed << "\n\n";
	quitProgram = Termination(optimalPath, cycle, maze, grid, _window);
	}
}