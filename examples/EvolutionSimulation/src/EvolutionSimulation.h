#pragma once

#include <evosim/EvoSim.h>

#include <cstddef>
#include <memory>
#include <optional>
#include <raylib.h>
#include <vector>

#include "Object2D.h"
#include <evosim/neuralnetwork/Genome.h>

namespace evosim {

class Agent;
class Food;

struct AgentSpawnParams {
  std::optional<Vector2> position;
  std::optional<Genome> genome;

  float initial_energy = 100.0f;
};

struct FoodSpawnParams {
  std::optional<Vector2> position;

  float initial_energy = 100.0f;
};

class EvolutionSimulation final : public ISimulation {
public:
  EvolutionSimulation();
  ~EvolutionSimulation() override;

  void update(float p_dt) override;
  void render() const override;
  void render_selection_overlay(const Object &p_object) const override;

  Object *find_object_at(Vector2 p_world_position) override;
  Object *find_object_by_id(Object::ID p_id) override;

  void draw_inspector(Object &p_object) override;
  void draw_statistics() override;

  std::size_t get_agent_count() const;

private:
  std::vector<std::unique_ptr<Agent>> m_population;
  std::vector<std::unique_ptr<Food>> m_food;
  int m_spawn_distance = 1000;

  bool is_point_inside_agent(Vector2 p_point, const Object2D &p_object);
  std::unique_ptr<Agent> create_agent(AgentSpawnParams p_params);
  std::unique_ptr<Food> create_food(FoodSpawnParams p_params);
  Vector2 get_random_world_position();
};

} // namespace evosim
