#pragma once

#include "Food.h"
#include "neural/NeuralNetwork.h"
#include "raylib.h"
#include <array>
#include <memory>
#include <vector>

using Genome = std::array<float, 12>;

struct ClosestFoodData {
  Food *food;
  float direction;
  float distance;
};

class Agent {
public:
  Agent(Vector2 p_position);
  Agent(Vector2 p_position, std::array<float, 12> p_genome);
  ~Agent();

  void update(float p_deltaTime,
              const std::vector<std::unique_ptr<Food>> &p_all_food);
  void render();

  bool is_dead();
  float get_energy();
  float get_reproduce_threshold();
  float get_reproduction_cooldown();
  Vector2 get_position();
  Genome repruduce();

private:
  NeuralNetwork *m_neural_network;

  Vector2 m_position;
  float m_energy = 1.0F;
  float m_speed = 0;
  float m_rotation = 0;
  float m_reproduction_threshold = 1.1F;
  float m_reproduction_cooldown = 5.F;

  ClosestFoodData
  find_closest(const std::vector<std::unique_ptr<Food>> &p_all_food);
  float get_distance_to_border() const;
};
