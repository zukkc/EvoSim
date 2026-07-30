#include "Agent.h"
#include <raylib.h>

Agent::Agent(int p_xpos, int p_ypos) {
  m_xpos = p_xpos;
  m_ypos = p_ypos;
}

void Agent::update(const std::vector<Food *> &p_all_food) {
  Food *food = find_closest(p_all_food);
  m_energy -= 0.0001;
  
  if (m_energy <= 0) {
    delete this;
  }
}

void Agent::render() { 
    DrawCircle(m_xpos, m_ypos, 10.0F, WHITE);
    DrawRectangle(m_xpos - 20, m_ypos - 20, 40, 5, GRAY);
    DrawRectangle(m_xpos - 20, m_ypos - 20, (int)40*m_energy, 5, RED);
}

Food *Agent::find_closest(const std::vector<Food *> p_all_food) {
  Food *closest_food;
  int closest_result = 9999;

  for (auto *food : p_all_food) {
    if (food == nullptr) {
      continue;
    }

    int result_x = m_xpos - food->get_x_pos();
    int result_y = m_ypos - food->get_y_pos();
    int result_final = result_x + result_y;

    if (result_final < closest_result) {
      closest_result = result_final;
      closest_food = food;
    }
  }

  return closest_food;
}