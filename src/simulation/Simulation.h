#pragma once
#include "Agent.h"
#include "Food.h"
#include <memory>
#include <optional>
#include <raylib.h>
#include <vector>

namespace evosim {

struct AgentSpawnParams {
  std::optional<Vector2> position;
  std::optional<Genome> genome;

  float initial_energy = 100.0f;
  int id = 0;
};

struct FoodSpawnParams {
  std::optional<Vector2> position;

  float initial_energy = 100.0f;
  int id = 1;
};

struct Transform {
  Vector2 position{};
  float rotation = 0.0f;
  Vector2 scale{1.0f, 1.0f};
};

class Simulation {
public:
  Simulation();
  void update(float p_dt);
  void render();

  Agent *find_agent_at(Vector2 world_position);
  void set_active_in_inspector(Agent *p_agent);

  size_t get_agent_count();
  Agent *get_active_in_inspector();

private:
  std::vector<std::unique_ptr<Agent>> m_population;
  std::vector<std::unique_ptr<Food>> m_food;
  Agent *m_active_in_ispector = nullptr;
  int m_reserved_ids = 0;
  int m_spawn_distance = 1000;

  bool is_point_inside_agent(Vector2 p_point, const Agent &p_agent);
  std::unique_ptr<Agent> create_agent(AgentSpawnParams p_params);
  std::unique_ptr<Food> create_food(FoodSpawnParams p_params);
  Vector2 get_random_world_position();
};

} // namespace evosim