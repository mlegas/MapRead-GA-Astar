#include <vector>
#include <memory>
#include <random>
#pragma once

class Cycle;
class Chromosome;

void Mutation(std::vector<std::shared_ptr<Chromosome>> &_offspring, Cycle &_cycle, std::uniform_real_distribution<float> &_distribution, std::random_device &_generator);