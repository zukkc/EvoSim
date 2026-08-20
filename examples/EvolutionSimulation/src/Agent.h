#pragma once

#include "raylib.h"
#include <array>
#include <memory>
#include <vector>

#include "Object2D.h"
#include <evosim/neuralnetwork/Genome.h>

namespace evosim {

class NeuralNetwork;
class Food;

struct ClosestFoodData {
  Food *food;
  float direction;
  float distance;
};

class Agent : public Object2D {
public:
  Agent(Vector2 p_position);
  Agent(Vector2 p_position, std::array<float, 12> p_genome);
  ~Agent();

  void update(float p_deltaTime,
              const std::vector<std::unique_ptr<Food>> &p_all_food);
  void render() const override;

  bool is_dead() const;
  float get_energy() const;
  const Genome &get_genome() const;
  float get_reproduce_threshold() const;
  float get_reproduction_cooldown() const;
  float get_radius() const;

  Genome repruduce();

private:
  std::unique_ptr<NeuralNetwork> m_neural_network;

  float m_energy = 1.0F;
  float m_speed = 0.0F;
  float m_reproduction_threshold = 1.1F;
  float m_reproduction_cooldown = 5.0F;

  ClosestFoodData
  find_closest(const std::vector<std::unique_ptr<Food>> &p_all_food);
  float get_distance_to_border() const;
};

} // namespace evosim
