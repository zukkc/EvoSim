#pragma once

#include <evosim/neuralnetwork/Genome.h>

#include <random>

namespace evosim {

class NeuralNetwork {
public:
  NeuralNetwork();
  explicit NeuralNetwork(Genome p_genome);

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
