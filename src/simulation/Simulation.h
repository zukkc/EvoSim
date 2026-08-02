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
  size_t get_agent_count();

private:
  std::vector<std::unique_ptr<Agent>> m_population;
  std::vector<std::unique_ptr<Food>> m_food;
  
};