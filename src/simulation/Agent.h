#pragma once

#include "raylib.h"
#include <array>
#include <memory>
#include <vector>

#include "Food.h"
#include "neural/NeuralNetwork.h"

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

  int get_id() const;
  bool is_dead() const;
  float get_energy() const;
  const Genome &get_genome() const;
  float get_reproduce_threshold() const;
  float get_reproduction_cooldown() const;
  Vector2 get_position() const;
  float get_radius() const;

  Genome repruduce();
  void set_active(bool p_active);

private:
  NeuralNetwork *m_neural_network;

  Vector2 m_position;
  float m_energy = 1.0F;
  float m_speed = 0;
  float m_rotation = 0;
  float m_reproduction_threshold = 1.1F;
  float m_reproduction_cooldown = 5.0F;
  float m_radius = 10.0F;
  bool m_is_active = false;

  ClosestFoodData
  find_closest(const std::vector<std::unique_ptr<Food>> &p_all_food);
  float get_distance_to_border() const;
};
