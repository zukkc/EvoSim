#pragma once
#include "Agent.h"
#include "Food.h"
#include <memory>
#include <raylib.h>
#include <vector>

class Simulation {
public:
  Simulation();
  void update(float p_dt);
  void render();

  Agent *find_agent_at(Vector2 world_position);
  void set_active_in_inspector(Agent* p_agent);
  
  size_t get_agent_count();
  Agent *get_active_in_inspector();

private:
  std::vector<std::unique_ptr<Agent>> m_population;
  std::vector<std::unique_ptr<Food>> m_food;
  Agent *m_active_in_ispector = nullptr;

  bool is_point_inside_agent(Vector2 p_point, const Agent &p_agent);
};