#include "NeuralNetwork.h"
#include <array>
#include <cmath>

NeuralNetwork::NeuralNetwork()
    : m_generator(std::random_device{}()), m_distribution(-1.0f, 1.0f) {
  std::array<float, 12> genome;
  for (auto &gen : genome) {
    gen = m_distribution(m_generator);
  }
  m_genome = genome;
}

NeuralNetwork::NeuralNetwork(std::array<float, 12> p_genome)
    : m_genome(p_genome), m_generator(std::random_device{}()), m_distribution(-1.0f, 1.0f) {
}

std::array<float, 2> NeuralNetwork::forward(std::array<float, 5> p_inputs) {

  std::array<float, 2> output;
  output[0] = std::tanh(p_inputs[0] * m_genome[0] + p_inputs[1] * m_genome[1] +
                        p_inputs[2] * m_genome[2] + p_inputs[3] * m_genome[3] +
                        p_inputs[4] * m_genome[4] + m_genome[5]);

  output[1] = std::tanh(p_inputs[0] * m_genome[6] + p_inputs[1] * m_genome[7] +
                        p_inputs[2] * m_genome[8] + p_inputs[3] * m_genome[9] +
                        p_inputs[4] * m_genome[10] + m_genome[11]);

  return output;
}

std::array<float, 12> NeuralNetwork::mutate() {
  auto new_genome = m_genome;
  for (auto &gen : new_genome) {
    gen += m_distribution(m_generator) * m_mutate_ratio;
  }
  return new_genome;
}