#pragma once

#include <random>
#include "Genome.h"

namespace evosim {

class NeuralNetwork {
public:
  NeuralNetwork();
  NeuralNetwork(Genome p_genome);
  // in:    direction_to_food, distance_to_food, energy, distance_to_border,
  // out:   speed, direction
  NeuronOutputs forward(NeuronInputs p_inputs);
  Genome mutate();

  const Genome &get_genome() const;

private:
  Genome m_genome;
  float m_mutate_ratio = 0.02F;
  std::mt19937 m_generator;
  std::uniform_real_distribution<float> m_distribution;
};

} // namespace evosim
