#pragma once
#include <raylib.h>
#include <vector>
#include "Agent.h"
#include "Food.h"

class World {
public:    
  World();
  ~World();
  Color backgroundColor = GREEN;
  void update();
  void render();
    
private:
  std::vector<Agent*> m_population;
  std::vector<Food*> m_food;
};