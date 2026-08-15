#pragma once
#include <cstddef>
#include <memory>
#include <optional>
#include <raylib.h>
#include <vector>

#include "Object2D.h"
#include "neural/Genome.h"

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

class Simulation {
public:
  enum Speed {
    SLOWER,
    NORMAL,
    FASTER,
  };

public:
  Simulation();
  ~Simulation();
  void update(float p_dt);
  void render();

  void start_simulation();
  void end_simulation();
  void set_simulation_speed(Speed p_speed);
  float get_simulation_speed() const;
  Object *find_object_at(Vector2 p_world_position);
  Object *get_object_by_id(Object::ID p_id);
  bool contains_object(const Object *p_object) const;
  void set_active_object(Object *p_object);

  bool is_running() const;
  Object *get_active_object();
  size_t get_agent_count();

private:
  std::vector<std::unique_ptr<Agent>> m_population;
  std::vector<std::unique_ptr<Food>> m_food;
  std::optional<Object::ID> m_active_object_id;
  int m_spawn_distance = 1000;
  bool m_running = false;
  float m_speed = 1;

  bool is_point_inside_agent(Vector2 p_point, const Object2D &p_object);
  std::unique_ptr<Agent> create_agent(AgentSpawnParams p_params);
  std::unique_ptr<Food> create_food(FoodSpawnParams p_params);
  Vector2 get_random_world_position();
};

} // namespace evosim
