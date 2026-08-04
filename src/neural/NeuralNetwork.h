#pragma once

#include <array>
#include <random>

#include "neural/Genome.h"

namespace evosim {

class NeuralNetwork {
public:
  NeuralNetwork();
  NeuralNetwork(std::array<float, 12> p_genome);
  // in:    direction_to_food, distance_to_food, energy, distance_to_border,
  // out:   speed, direction
  std::array<float, 2> forward(std::array<float, 5> p_inputs);
  Genome mutate();

  const Genome &get_genome() const;

private:
  std::array<float, 12> m_genome;
  float m_mutate_ratio = 0.08F;
  std::mt19937 m_generator;
  std::uniform_real_distribution<float> m_distribution;
};

} // namespace evosim
