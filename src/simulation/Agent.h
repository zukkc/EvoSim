#pragma once
#include "Food.h"
#include <raylib.h>
#include <vector>

class Agent {
public:
  Agent(int p_xpos, int p_ypos);
  void update(const std::vector<Food *> &p_all_food);
  void render();

private:
  float m_energy = 1.f;
  int m_xpos;
  int m_ypos;

  Food *find_closest(const std::vector<Food *> p_all_food);
};