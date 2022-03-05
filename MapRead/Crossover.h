#include <vector>
#include <memory>
#include <random>
#pragma once

class Chromosome;
class Cycle;

std::vector<std::shared_ptr<Chromosome>> Crossover(Cycle &_cycle, std::random_device &_generator, std::uniform_real_distribution<float> &_distribution, std::vector<int> &_selectedChromosomes);